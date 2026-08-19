#pragma once

// ── 配置模板：复制为 src/config.h 并填写真实值 ──────────────────────
// src/config.h 已在 .gitignore 中，不会进入版本库

// 1 = 离线演示数据，不连接 Wi-Fi/iKuai；0 = 使用下面的真实配置
#define APP_DEMO_MODE 1

// 1 = 减少页面滑动和流星动效，保留曲线滚动；0 = 标准动效
#define APP_REDUCED_MOTION 0

#define APP_WIFI_SSID "YOUR_SSID"
#define APP_WIFI_PASS "YOUR_PASSWORD"

#define APP_TZ "CST-8"

#define APP_BL_PCT 30

// 夜间自动降背光(SNTP 授时后生效;手动息屏优先)
// 时段跨零点也可,例如 23~7 表示 23:00~次日 07:00
#define APP_NIGHT_START 23
#define APP_NIGHT_END   7
#define APP_BL_NIGHT_PCT 8

// ── iKuai 路由器监视 ───────────────────────────────────────────────
// token 获取：~/.ikuai-cli/config.json（ikuai-cli auth set-token）
#define IKUAI_HOST  "https://192.0.2.1"
#define IKUAI_TOKEN "REPLACE_WITH_IKUAI_TOKEN"
