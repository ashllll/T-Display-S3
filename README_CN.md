# T-Display-S3 iKuai 小屏监控

这是一个面向 LILYGO T-Display-S3 的独立小屏监控项目：通过 Wi‑Fi 读取 iKuai 路由器数据，在板载 ST7789 屏幕上显示 WAN 状态、Ping、上下行速率、客户端和无线状态。

项目重点是“拿起来就能读懂”的紧凑信息墙：黑底、少量高饱和状态色、大字号实时速率和无网格趋势曲线。默认提供离线演示模式，不会在首次启动时连接任何网络。

## UI 预览

![主界面与核心监控页](examples/ikuai_widget/docs/ui-preview.svg)

![页面 1–4](examples/ikuai_widget/docs/ui-pages-preview.svg)

![页面 5–8](examples/ikuai_widget/docs/ui-pages2-preview.svg)

## 功能概览

| 页面 | 内容 | 更新来源 |
| --- | --- | --- |
| 1 | WAN 状态、Ping、上下行速率、三色趋势曲线 | `monitoring/system`，1 秒 |
| 2 | 下行速率焦点页、上行副行、会话峰值 | `monitoring/system` |
| 3 | 全屏滚动趋势曲线与 Ping | `monitoring/system` + ICMP |
| 4 | 本机 IP、客户端数、运行时间、堆内存 | 本机状态 |
| 5 | 路由器 CPU、内存、温度、运行时间、版本 | `monitoring/system` |
| 6 | 双 WAN 公网 IP、网关和在线状态 | `monitoring/interfaces-status`，3 秒轮询 |
| 7 | 下载流量 Top 3 客户端 | `monitoring/clients-online`，3 秒轮询 |
| 8 | AC、AP、2.4G/5G 终端状态 | AC 和无线统计接口，3 秒轮询 |

扩展接口采用轮转请求，每 3 秒只请求一组数据，减少对路由器的压力。

BOOT 键（GPIO0）操作：单击翻页，双击回到主页，长按息屏/唤醒；60 秒无操作自动回主页。

## 硬件与显示驱动

- 主控：ESP32-S3R8，16MB Flash，8MB OPI PSRAM
- 屏幕：ST7789，横屏 320×170，8-bit i80 并口
- 外设电源：GPIO15，必须在 LCD 初始化前拉高
- LCD 数据：GPIO39/40/41/42/45/46/47/48
- LCD 控制：RST GPIO5、CS GPIO6、DC GPIO7、WR GPIO8、背光 GPIO38
- BOOT 按键：GPIO0

此项目使用 ESP-IDF `esp_lcd` 和 LVGL 9；iKuai 固件入口固定为 `examples/ikuai_widget`，其他 Arduino/LVGL 8 示例不属于本项目运行路径。

## 构建

```bash
cd examples/ikuai_widget
pio run -e t-display-s3
```

项目通过 ESP-IDF Component Manager（`src/idf_component.yml`）固定使用 LVGL 9.2.2，并提交 `dependencies.lock` 保证依赖版本稳定。干净检出后无需私有文件即可直接编译，默认使用仓库内的示例配置运行离线演示模式：

```bash
pio run -e t-display-s3
```

如果要连接真实 iKuai，再创建本地配置文件：

```bash
cp src/config.example.h src/config.h
cp src/ikuai_cert.example.h src/ikuai_cert.h
```

然后：

1. 在 `src/config.h` 中填写 Wi‑Fi、iKuai 地址和 Bearer Token。
2. 将 `APP_DEMO_MODE` 改为 `0`。
3. 在 `src/ikuai_cert.h` 中填写路由器 HTTPS CA 证书。
4. 先完成编译，再明确执行上传命令；两个本地配置文件都不要提交。

真实凭据、证书、串口路径和构建产物不会提交到仓库。

## 目录

```text
examples/ikuai_widget/
├── src/main.c                 # 应用入口
├── src/lcd_driver.c           # T-Display-S3 ST7789 i80 驱动
├── src/lv_port_disp.c         # LVGL 显示适配
├── src/desktop_widget.c       # 8 页监控 UI 与动画
├── src/ikuai_monitor.c        # iKuai API、Ping 与数据缓存
├── src/fonts/                 # D-DIN LVGL 字体
├── src/idf_component.yml      # 固定 LVGL 9.2.2 依赖
├── components/lv_conf.h       # 面向本板的 LVGL 功能裁剪配置
├── docs/                      # README 使用的 UI 预览图
└── platformio.ini             # t-display-s3 构建入口
```

## 验证边界

当前已用 `pio run -e t-display-s3` 验证主机侧依赖和固件编译；屏幕方向、背光、按键、Wi‑Fi、iKuai HTTPS 和实际曲线效果仍需在真实 T-Display-S3 上验证。烧录成功本身不等于屏幕和网络功能验收通过，仓库也不包含路由器凭据。
