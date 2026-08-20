#pragma once

#include <stdint.h>
#include <stdbool.h>

// iKuai 路由器实时监视数据（https + Bearer token + 固定证书）
// - system 端点 1s 轮询（CPU/内存/在线数/实时上下行速率）
// - ICMP ping 网关 1s 采样（延迟曲线）
// - 60 点曲线缓存（1 秒/点，实时滚动窗口）

#define IKUAI_CURVE_MAX 60

typedef enum {
    IKUAI_LINK_WAIT = 0,
    IKUAI_LINK_ONLINE,
    IKUAI_LINK_NETWORK_ERROR,
    IKUAI_LINK_TIMEOUT,
    IKUAI_LINK_AUTH_ERROR,
    IKUAI_LINK_HTTP_ERROR,
} ikuai_link_state_t;

typedef struct {
    bool ok;
    uint32_t ts;
    float cpu_pct;
    float mem_pct;
    uint32_t online_cnt;
    uint32_t conn_cnt;
    uint32_t down_bps;      // 实时下行 B/s（由 total_down 采样差分）
    uint32_t up_bps;        // 实时上行 B/s（由 total_up 采样差分）
} ikuai_sys_t;

typedef struct {
    bool ok;
    uint32_t ts;
    int head;                          // 下一个写入位置
    int n;                             // 已填充点数（<= 60）
    float ping_ms[IKUAI_CURVE_MAX];    // 网关延迟 ms
    uint32_t down[IKUAI_CURVE_MAX];    // B/s
    uint32_t up[IKUAI_CURVE_MAX];      // B/s
} ikuai_curve_t;

// ── 扩展信息（3s 轮询，轮询制:每 tick 只发一个额外请求）──
typedef struct { char name[12]; char ip[16]; char gateway[16]; int ok; } ikuai_wan_t;
typedef struct { char name[24]; char ip[16]; uint32_t down_bps; } ikuai_client_t;

typedef struct {
    bool ok;
    uint32_t system_ts;             // system/health data last successful sample
    float    cpu_temp;        // °C（system 端点 cputemp[0]，1s 更新）
    uint32_t uptime_sec;      // 路由运行时间（system 端点 uptime）
    char     version[16];     // 固件版本 verstring
    uint32_t wan_ts;                // interfaces-status last successful sample
    int  wan_cnt;             // WAN 线路数（interfaces-status，3s）
    ikuai_wan_t    wan[2];
    uint32_t clients_ts;            // clients-online last successful sample
    int  client_cnt;          // 下行 Top3（clients-online，3s）
    ikuai_client_t client[3];
    uint32_t ac_ts;                 // AC/wireless last successful sample
    int  ac_on;               // AC 功能开关（network/ac/services，5s）
    int  ap_online, ap_count; // AP 在线/总数（wireless-statistics）
    int  clt_2g, clt_5g;      // 2.4G/5G 终端数
} ikuai_extra_t;

bool ikuai_get_extra(ikuai_extra_t *out);

void ikuai_monitor_start(void);
bool ikuai_get_sys(ikuai_sys_t *out);
bool ikuai_get_curve(ikuai_curve_t *out);
bool ikuai_recently_ok(void);
ikuai_link_state_t ikuai_get_link_state(void);
void ikuai_monitor_network_changed(void);
