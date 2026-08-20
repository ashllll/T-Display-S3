// iKuai 路由器实时监视：HTTPS API + ICMP ping
// - system 端点 1s 轮询：实时上下行速率、CPU/内存/在线数
// - ping 网关 1s 采样：延迟曲线
// - 60 点环形缓存，供 UI 画实时滚动曲线
#include "ikuai_monitor.h"
#if __has_include("ikuai_cert.h")
#include "ikuai_cert.h"
#else
#include "ikuai_cert.example.h"
#endif
#if __has_include("config.h")
#include "config.h"
#else
#include "config.example.h"
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_timer.h"
#include "apps/ping/ping_sock.h"   // IDF 6.0 无 esp_ping 组件，用 lwip ping_sock
#include "esp_netif.h"

static const char *TAG = "ikuai";

#define API_BASE IKUAI_HOST
#define HTTP_TIMEOUT_MS 5000

static SemaphoreHandle_t s_mux;
static ikuai_sys_t    s_sys;
static ikuai_extra_t  s_extra;
static ikuai_wan_t    s_extra_wan_tmp[2];
static ikuai_client_t s_extra_client_tmp[3];
static ikuai_curve_t  s_curve;
static volatile uint32_t s_last_ok_ts = 0;
static volatile float s_latest_ping_ms = -1;   // ping 回调只存最新值
static volatile ikuai_link_state_t s_link_state = IKUAI_LINK_WAIT;
static uint64_t s_prev_total_down;
static uint64_t s_prev_total_up;
static uint64_t s_prev_down_us;
static uint64_t s_prev_up_us;
static bool s_prev_down_valid;
static bool s_prev_up_valid;
static volatile bool s_network_changed;
static uint32_t s_api_rate_scale = 1;

// ─── HTTP（复用 client，IDF 6.0.1 每次 init/cleanup 泄漏 ~5KB）───

typedef struct {
    char *buf;
    int len;
    int cap;
    bool truncated;
} resp_t;
static esp_http_client_handle_t s_client = NULL;
static resp_t s_resp;
static bool s_logged_api_ok;

static esp_err_t on_http_evt(esp_http_client_event_t *evt) {
    if (evt->event_id == HTTP_EVENT_ON_DATA) {
        resp_t *r = (resp_t *)evt->user_data;
        int n = evt->data_len;
        int room = r->cap - r->len - 1;
        if (room <= 0) {
            r->truncated = true;
            return ESP_OK;
        }
        int copy = n < room ? n : room;
        memcpy(r->buf + r->len, evt->data, copy);
        r->len += copy;
        r->buf[r->len] = 0;
        if (copy != n) r->truncated = true;
    }
    return ESP_OK;
}

static bool api_get(const char *path, char *buf, int cap) {
    char url[200];
    int url_len = snprintf(url, sizeof(url), "%s%s", API_BASE, path);
    if (url_len <= 0 || url_len >= (int)sizeof(url)) {
        ESP_LOGW(TAG, "request URL too long: %s", path);
        s_link_state = IKUAI_LINK_HTTP_ERROR;
        return false;
    }
    if (!s_client) {
        esp_http_client_config_t cfg = {
            .url = API_BASE "/api/v4.0/monitoring/system",
            .method = HTTP_METHOD_GET,
            .timeout_ms = HTTP_TIMEOUT_MS,
            .cert_pem = ikuai_cert_pem,
            .skip_cert_common_name_check = true,
            .event_handler = on_http_evt,
            .user_data = &s_resp,
            .user_agent = "T-Display-S3/1.0",
        };
        s_client = esp_http_client_init(&cfg);
        if (!s_client) {
            s_link_state = IKUAI_LINK_NETWORK_ERROR;
            return false;
        }
        ESP_LOGI(TAG, "http client initialized once");
    }
    s_resp.buf = buf;
    s_resp.len = 0;
    s_resp.cap = cap;
    s_resp.truncated = false;
    esp_http_client_set_url(s_client, url);
    char auth[192];
    int auth_len = snprintf(auth, sizeof(auth), "Bearer %s", IKUAI_TOKEN);
    if (auth_len <= 0 || auth_len >= (int)sizeof(auth)) {
        ESP_LOGW(TAG, "Bearer token is too long");
        s_link_state = IKUAI_LINK_AUTH_ERROR;
        return false;
    }
    esp_http_client_set_header(s_client, "Authorization", auth);
    esp_err_t err = esp_http_client_perform(s_client);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "http fail %s: %s", path, esp_err_to_name(err));
        s_link_state = err == ESP_ERR_TIMEOUT ? IKUAI_LINK_TIMEOUT : IKUAI_LINK_NETWORK_ERROR;
        return false;
    }
    int status = esp_http_client_get_status_code(s_client);
    if (status < 200 || status >= 300 || s_resp.truncated) {
        ESP_LOGW(TAG, "http invalid response %s: status=%d bytes=%d truncated=%d",
                 path, status, s_resp.len, s_resp.truncated);
        if (status == 401 || status == 403) s_link_state = IKUAI_LINK_AUTH_ERROR;
        else s_link_state = IKUAI_LINK_HTTP_ERROR;
        return false;
    }
    if (!s_logged_api_ok) {
        s_logged_api_ok = true;
        ESP_LOGI(TAG, "api online: status=%d bytes=%d", status, s_resp.len);
    }
    s_link_state = IKUAI_LINK_ONLINE;
    return s_resp.len > 0;
}

// ─── 极简 JSON 提取 ─────────────────────────────────────────────────

static bool array_first_str(const char *s, const char *key, char *out, int cap) {
    char pat[32];
    snprintf(pat, sizeof(pat), "\"%s\":[\"", key);
    const char *p = strstr(s, pat);
    if (!p) return false;
    p += strlen(pat);
    int i = 0;
    while (*p && *p != '"' && i < cap - 1) out[i++] = *p++;
    out[i] = 0;
    return i > 0;
}

static bool kv_num_range(const char *start, const char *end, const char *key, double *out) {
    char pat[32];
    snprintf(pat, sizeof(pat), "\"%s\":", key);
    const char *p = strstr(start, pat);
    if (!p || p > end) return false;
    p += strlen(pat);
    while (*p == ' ') p++;
    char *endp;
    double v = strtod(p, &endp);
    if (endp == p || endp > end) return false;
    *out = v;
    return true;
}

static uint32_t rate_from_counter(uint64_t total, uint64_t now_us,
                                  uint64_t *prev_total, uint64_t *prev_us,
                                  bool *valid, bool *sample_valid,
                                  uint32_t fallback) {
    uint32_t result = fallback;
    if (sample_valid) *sample_valid = false;
    if (*valid && total >= *prev_total && now_us > *prev_us) {
        uint64_t delta = total - *prev_total;
        uint64_t elapsed_us = now_us - *prev_us;
        uint64_t bytes_per_sec = (delta / elapsed_us) * 1000000ULL;
        bytes_per_sec += ((delta % elapsed_us) * 1000000ULL) / elapsed_us;
        result = bytes_per_sec > UINT32_MAX ? UINT32_MAX : (uint32_t)bytes_per_sec;
        if (sample_valid) *sample_valid = true;
    }
    *prev_total = total;
    *prev_us = now_us;
    *valid = true;
    return result;
}

// iKuai firmware versions have exposed stream rates as either B/s or KB/s.
// Keep the raw field as fallback and only promote the counter delta when its
// relationship to the raw value is plausible, avoiding a silent 1024x error.
static uint32_t choose_rate(uint32_t direct_bps, bool direct_valid,
                            uint32_t counter_bps, bool counter_valid,
                            uint32_t *scale_out) {
    if (scale_out) *scale_out = 1;
    if (!counter_valid) return direct_valid ? direct_bps : 0;
    if (!direct_valid || direct_bps == 0) return counter_bps;

    uint64_t d = direct_bps;
    uint64_t c = counter_bps;
    bool same_unit = c >= d / 4 && c <= d * 4;
    bool direct_is_kib = c >= d * 512 && c <= d * 2048;
    if (direct_is_kib && scale_out) *scale_out = 1024;
    return (same_unit || direct_is_kib) ? counter_bps : direct_bps;
}

static bool kv_str_range(const char *start, const char *end, const char *key,
                         char *out, int cap) {
    char pat[32];
    snprintf(pat, sizeof(pat), "\"%s\":\"", key);
    const char *p = strstr(start, pat);
    if (!p || p > end) return false;
    p += strlen(pat);
    int i = 0;
    while (*p && *p != '"' && i < cap - 1) out[i++] = *p++;
    out[i] = 0;
    return i > 0;
}

// 解析 system 响应，写入 sys 缓存 + 曲线缓存
static void parse_system(const char *resp) {
    ikuai_sys_t s = { 0 };
    char tmp[16];
    double v;
    bool has_total_down = false;
    bool has_total_up = false;
    uint64_t total_down = 0;
    uint64_t total_up = 0;
    uint32_t direct_down = 0, direct_up = 0;
    bool has_direct_down = false, has_direct_up = false;
    if (array_first_str(resp, "cpu", tmp, sizeof(tmp))) s.cpu_pct = (float)atof(tmp);
    const char *mem = strstr(resp, "\"memory\":{");
    if (mem) {
        if (kv_str_range(mem, mem + 300, "used", tmp, sizeof(tmp)))
            s.mem_pct = (float)atof(tmp);
    }
    const char *ou = strstr(resp, "\"online_user\":{");
    if (ou && kv_num_range(ou, ou + 200, "count", &v)) s.online_cnt = (uint32_t)v;
    const char *st = strstr(resp, "\"stream\":{");
    if (st) {
        if (kv_num_range(st, st + 300, "connect_num", &v)) s.conn_cnt = (uint32_t)v;
        // 保留瞬时字段原值；是否需要 KB/s 转换由累计计数的比例运行时确认。
        if (kv_num_range(st, st + 300, "download", &v))
            direct_down = v > 0 ? (uint32_t)v : 0, has_direct_down = true;
        if (kv_num_range(st, st + 300, "upload", &v))
            direct_up = v > 0 ? (uint32_t)v : 0, has_direct_up = true;
        if (kv_num_range(st, st + 300, "total_down", &v) && v >= 0)
            total_down = (uint64_t)v, has_total_down = true;
        if (kv_num_range(st, st + 300, "total_up", &v) && v >= 0)
            total_up = (uint64_t)v, has_total_up = true;
    }
    // HTTP 2xx 已经代表本次采样成功；空闲 WAN 的速率和在线数都可能为 0。
    s.ok = true;
    uint64_t now_us = (uint64_t)esp_timer_get_time();
    bool down_counter_ok = false, up_counter_ok = false;
    uint32_t down_counter = has_total_down
        ? rate_from_counter(total_down, now_us, &s_prev_total_down, &s_prev_down_us,
                            &s_prev_down_valid, &down_counter_ok, direct_down)
        : (s_prev_down_valid = false, 0);
    uint32_t up_counter = has_total_up
        ? rate_from_counter(total_up, now_us, &s_prev_total_up, &s_prev_up_us,
                            &s_prev_up_valid, &up_counter_ok, direct_up)
        : (s_prev_up_valid = false, 0);
    uint32_t down_scale = 1, up_scale = 1;
    s.down_bps = choose_rate(direct_down, has_direct_down, down_counter,
                             down_counter_ok, &down_scale);
    s.up_bps = choose_rate(direct_up, has_direct_up, up_counter,
                           up_counter_ok, &up_scale);
    if (down_scale == 1024 || up_scale == 1024) s_api_rate_scale = 1024;
    else if (down_counter_ok || up_counter_ok) s_api_rate_scale = 1;
    s.ts = (uint32_t)(now_us / 1000000);
    if (s.ok) s_last_ok_ts = s.ts;

    xSemaphoreTake(s_mux, portMAX_DELAY);
    // system 响应附带的健康字段:cputemp[]/uptime/verinfo.verstring（1s 同步）
    {   // "cputemp":[53] 数字数组取首个
        const char *ct = strstr(resp, "\"cputemp\":[");
        if (ct) { s_extra.cpu_temp = (float)strtod(ct + 11, NULL); }
        const char *ut = strstr(resp, "\"uptime\":");
        if (ut) { s_extra.uptime_sec = (uint32_t)strtoul(ut + 9, NULL, 10); }
        const char *vi = strstr(resp, "\"verinfo\":{");
        if (vi) kv_str_range(vi, vi + 400, "verstring", s_extra.version, sizeof(s_extra.version));
    }
    s_sys = s;
    s_extra.system_ts = s.ts;
    s_extra.ok = true;
    // 速率 + ping 统一进曲线（1s 采样，由本函数推进槽位）
    int h = s_curve.head;
    s_curve.down[h] = s.down_bps;
    s_curve.up[h] = s.up_bps;
    s_curve.ping_ms[h] = s_latest_ping_ms;
    if (s_curve.n < IKUAI_CURVE_MAX) s_curve.n++;
    s_curve.head = (h + 1) % IKUAI_CURVE_MAX;
    s_curve.ts = s.ts;
    xSemaphoreGive(s_mux);
}


// ─── 扩展端点解析（极简 strstr 提取，与现有风格一致）────────────────

// 从 JSON 对象起点后提取首个 "key":"value" 字符串
static const char *next_obj(const char *p, const char *key) {
    char pat[24];
    snprintf(pat, sizeof(pat), "\"%s\":\"", key);
    return strstr(p, pat);
}

// WAN 线路:/monitoring/interfaces-status → iface_check[]
static void parse_wan(const char *resp) {
    const char *arr = strstr(resp, "\"iface_check\":[");
    if (!arr) return;
    int cnt = 0;
    const char *p = arr;
    while (cnt < 2 && (p = next_obj(p, "interface")) != NULL) {
        p += 13;
        ikuai_wan_t *w = &s_extra_wan_tmp[cnt];
        int i = 0;
        while (*p && *p != '"' && i < (int)sizeof(w->name) - 1) w->name[i++] = *p++;
        w->name[i] = 0;
        const char *obj_end = strchr(p, '}');
        if (!obj_end) obj_end = p + 300;
        kv_str_range(p, obj_end + 200, "ip_addr", w->ip, sizeof(w->ip));
        kv_str_range(p, obj_end + 200, "gateway", w->gateway, sizeof(w->gateway));
        char res[12] = "";
        kv_str_range(p, obj_end + 200, "result", res, sizeof(res));
        w->ok = strcmp(res, "success") == 0;
        cnt++;
        p = obj_end;
    }
    xSemaphoreTake(s_mux, portMAX_DELAY);
    s_extra.wan_cnt = cnt;
    for (int i = 0; i < cnt; i++) s_extra.wan[i] = s_extra_wan_tmp[i];
    s_extra.ok = true;
    s_extra.wan_ts = (uint32_t)(esp_timer_get_time() / 1000000);
    xSemaphoreGive(s_mux);
}

// 终端 Top3:/monitoring/clients-online?order_by=download&order=desc&limit=3
static void parse_clients(const char *resp) {
    const char *arr = strstr(resp, "\"data\":[");
    if (!arr) return;
    int cnt = 0;
    const char *p = arr;
    while (cnt < 3 && (p = strstr(p, "\"ip_addr\":\"")) != NULL) {
        p += strlen("\"ip_addr\":\"");
        ikuai_client_t *c = &s_extra_client_tmp[cnt];
        int i = 0;
        while (*p && *p != '"' && i < (int)sizeof(c->ip) - 1) c->ip[i++] = *p++;
        c->ip[i] = 0;
        const char *obj_end = strchr(p, '}');
        if (!obj_end) obj_end = p + 600;
        // 名称优先级:termname > comment > ip
        if (!kv_str_range(p, obj_end, "termname", c->name, sizeof(c->name)) &&
            !kv_str_range(p, obj_end, "comment", c->name, sizeof(c->name)))
            strncpy(c->name, c->ip, sizeof(c->name));
        double v;
        c->down_bps = kv_num_range(p, obj_end, "download", &v) ? (uint32_t)v : 0;
        cnt++;
        p = obj_end;
    }
    xSemaphoreTake(s_mux, portMAX_DELAY);
    s_extra.client_cnt = cnt;
    for (int i = 0; i < cnt; i++) s_extra.client[i] = s_extra_client_tmp[i];
    s_extra.ok = true;
    s_extra.clients_ts = (uint32_t)(esp_timer_get_time() / 1000000);
    for (int i = 0; i < cnt; i++) {
        uint64_t scaled = (uint64_t)s_extra.client[i].down_bps * s_api_rate_scale;
        s_extra.client[i].down_bps = scaled > UINT32_MAX ? UINT32_MAX : (uint32_t)scaled;
    }
    xSemaphoreGive(s_mux);
}

// AC 状态:/network/ac/services + /monitoring/wireless-statistics
static void parse_ac_status(const char *resp) {
    double v;
    const char *p = strstr(resp, "\"ac_status\":");
    xSemaphoreTake(s_mux, portMAX_DELAY);
    s_extra.ac_on = (p && kv_num_range(p, p + 30, "ac_status", &v)) ? (int)v : 0;
    s_extra.ok = true;
    s_extra.ac_ts = (uint32_t)(esp_timer_get_time() / 1000000);
    xSemaphoreGive(s_mux);
}

static void parse_ac_stat(const char *resp) {
    double ap_count = 0, ap_online = 0, c2 = 0, c5 = 0;
    const char *ap = strstr(resp, "\"ap_status\":{");
    if (ap) {
        kv_num_range(ap, ap + 200, "ap_count", &ap_count);
        kv_num_range(ap, ap + 200, "ap_online", &ap_online);
    }
    const char *cl = strstr(resp, "\"clt_status\":{");
    if (cl) {
        kv_num_range(cl, cl + 260, "clt_count_2g", &c2);
        kv_num_range(cl, cl + 260, "clt_count_5g", &c5);
    }
    xSemaphoreTake(s_mux, portMAX_DELAY);
    s_extra.ap_count = (int)ap_count; s_extra.ap_online = (int)ap_online;
    s_extra.clt_2g = (int)c2;         s_extra.clt_5g = (int)c5;
    xSemaphoreGive(s_mux);
}

// ─── Ping（ICMP 网关，1s 采样）──────────────────────────────────────

static esp_ping_handle_t s_ping = NULL;

static void on_ping_success(esp_ping_handle_t hdl, void *args) {
    uint32_t t = 0;
    esp_ping_get_profile(hdl, ESP_PING_PROF_TIMEGAP, &t, sizeof(t));
    s_latest_ping_ms = (float)t;
}

static void on_ping_timeout(esp_ping_handle_t hdl, void *args) {
    s_latest_ping_ms = -1;
}

static bool ping_start(void) {
    ip_addr_t gw;
    esp_netif_ip_info_t ipi;
    esp_netif_t *sta = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    if (!sta || esp_netif_get_ip_info(sta, &ipi) != ESP_OK ||
        ipi.ip.addr == 0 || ipi.gw.addr == 0) return false;
    ip_addr_copy_from_ip4(gw, ipi.gw);     // 用实际网关
    esp_ping_config_t cfg = ESP_PING_DEFAULT_CONFIG();
    cfg.target_addr = gw;
    cfg.count = ESP_PING_COUNT_INFINITE;   // 持续 ping（1s 间隔实时曲线）
    cfg.interval_ms = 1000;                // 1s 采样
    cfg.timeout_ms = 800;
    esp_ping_callbacks_t cbs = {
        .on_ping_success = on_ping_success,
        .on_ping_timeout = on_ping_timeout,
    };
    if (esp_ping_new_session(&cfg, &cbs, &s_ping) == ESP_OK) {
        esp_ping_start(s_ping);
        ESP_LOGI(TAG, "ping started (1s interval)");
        return true;
    }
    return false;
}

// ─── 轮询任务 ───────────────────────────────────────────────────────

static void poll_task(void *arg) {
    enum { BUF_SZ = 8192 };
    char *buf = (char *)malloc(BUF_SZ);
    if (!buf) { vTaskDelete(NULL); return; }
    uint32_t next = 0, next_ext = 0;
    int ext_slot = 0;
    for (;;) {
        uint32_t now = (uint32_t)(esp_timer_get_time() / 1000000);
        if (s_network_changed) {
            s_network_changed = false;
            if (s_ping) {
                esp_ping_stop(s_ping);
                esp_ping_delete_session(s_ping);
                s_ping = NULL;
            }
            s_prev_down_valid = false;
            s_prev_up_valid = false;
        }
        if (!s_ping) ping_start();
        if (now >= next) {
            next = now + 1;   // 1s 实时采样
            if (api_get("/api/v4.0/monitoring/system", buf, BUF_SZ))
                parse_system(buf);
        }
        if (now >= next_ext) {
            next_ext = now + 3;   // 扩展信息:3s 一轮,每轮只发一个请求
            switch (ext_slot) {
            case 0:
                if (api_get("/api/v4.0/monitoring/interfaces-status", buf, BUF_SZ))
                    parse_wan(buf);
                break;
            case 1:
                if (api_get("/api/v4.0/monitoring/clients-online?page=1&limit=3&order_by=download&order=desc", buf, BUF_SZ))
                    parse_clients(buf);
                break;
            case 2:
                if (api_get("/api/v4.0/network/ac/services", buf, BUF_SZ)) {
                    parse_ac_status(buf);
                    xSemaphoreTake(s_mux, portMAX_DELAY);
                    int ac = s_extra.ac_on;
                    xSemaphoreGive(s_mux);
                    if (ac && api_get("/api/v4.0/monitoring/wireless-statistics", buf, BUF_SZ))
                        parse_ac_stat(buf);
                }
                break;
            }
            ext_slot = (ext_slot + 1) % 3;
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ─── 对外接口 ───────────────────────────────────────────────────────

void ikuai_monitor_start(void) {
    s_mux = xSemaphoreCreateMutex();
    if (!s_mux) return;
    xTaskCreate(poll_task, "ikuai", 8192, NULL, 4, NULL);
    ESP_LOGI(TAG, "ikuai monitor started");
}

void ikuai_monitor_network_changed(void) {
    s_network_changed = true;
}

bool ikuai_get_sys(ikuai_sys_t *out) {
    if (!s_mux) return false;
    xSemaphoreTake(s_mux, portMAX_DELAY);
    *out = s_sys;
    xSemaphoreGive(s_mux);
    return out->ok && ikuai_recently_ok();
}

bool ikuai_get_curve(ikuai_curve_t *out) {
    if (!s_mux) return false;
    xSemaphoreTake(s_mux, portMAX_DELAY);
    *out = s_curve;
    xSemaphoreGive(s_mux);
    return out->n > 0;
}

bool ikuai_get_extra(ikuai_extra_t *out) {
    if (!s_mux) return false;
    xSemaphoreTake(s_mux, portMAX_DELAY);
    *out = s_extra;
    xSemaphoreGive(s_mux);
    return out->ok;
}

bool ikuai_recently_ok(void) {
    if (!s_last_ok_ts) return false;
    return (uint32_t)(esp_timer_get_time() / 1000000) - s_last_ok_ts < 10;
}

ikuai_link_state_t ikuai_get_link_state(void) {
    return s_link_state;
}
