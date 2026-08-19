# T-Display-S3 iKuai Monitor

This repository contains a focused iKuai router monitor for the LILYGO T-Display-S3. It reads router telemetry over Wi‑Fi and presents WAN status, ping, download/upload rates, clients, and wireless status on the onboard ST7789 display.

The UI is designed as a compact information wall: black background, restrained status colors, large live throughput numbers, and a grid-free rolling trend chart. The first build runs in offline demo mode and does not connect to a network.

## UI preview

![Main screen and core monitoring pages](examples/ikuai_widget/docs/ui-preview.svg)

![Pages 1–4](examples/ikuai_widget/docs/ui-pages-preview.svg)

![Pages 5–8](examples/ikuai_widget/docs/ui-pages2-preview.svg)

## Features

| Page | Content | Source |
| --- | --- | --- |
| 1 | WAN state, ping, download/upload rates, three-track trend | `monitoring/system`, 1 s |
| 2 | Throughput focus view, upload secondary row, session peak | `monitoring/system` |
| 3 | Full-screen rolling trend and ping | `monitoring/system` + ICMP |
| 4 | Local IP, clients, uptime, and heap | Local state |
| 5 | Router CPU, memory, temperature, uptime, and firmware | `monitoring/system` |
| 6 | Dual-WAN public IP, gateway, and link state | `monitoring/interfaces-status`, every 3 s |
| 7 | Top three clients by download rate | `monitoring/clients-online`, every 3 s |
| 8 | AC, AP, and 2.4 GHz/5 GHz client status | AC and wireless endpoints, every 3 s |

Extended endpoints rotate one request every three seconds to keep router load low.

BOOT (GPIO0): single press changes page, double press returns home, and long press toggles the display. The UI returns home after 60 seconds without input.

## Hardware and display driver

- MCU: ESP32-S3R8, 16 MB Flash, 8 MB OPI PSRAM
- Display: ST7789, landscape 320×170, 8-bit i80 parallel bus
- Peripheral power: GPIO15; pull it high before LCD initialization
- LCD data: GPIO39/40/41/42/45/46/47/48
- LCD control: RST GPIO5, CS GPIO6, DC GPIO7, WR GPIO8, backlight GPIO38
- BOOT button: GPIO0

The monitor uses the ESP-IDF `esp_lcd` driver and LVGL 9. The iKuai firmware entry point is `examples/ikuai_widget`; other Arduino/LVGL 8 examples are outside this project's runtime path.

## Build

```bash
cd examples/ikuai_widget
pio run -e t-display-s3
```

The project resolves LVGL 9.2.2 through ESP-IDF Component Manager (`src/idf_component.yml`) and keeps the lock file in `dependencies.lock`. A clean checkout builds in offline demo mode using the tracked example configuration; no private file is required for the first build.

To enable live iKuai monitoring, create local configuration files:

```bash
cp src/config.example.h src/config.h
cp src/ikuai_cert.example.h src/ikuai_cert.h
```

Then:

1. Fill in Wi‑Fi, iKuai host, and Bearer token in `src/config.h`.
2. Set `APP_DEMO_MODE` to `0`.
3. Put the router HTTPS CA certificate in `src/ikuai_cert.h`.
4. Build first, then explicitly run the upload command. Do not commit either local file.

Real credentials, certificates, serial paths, and build outputs are kept out of version control.

## Layout

```text
examples/ikuai_widget/
├── src/main.c                 # Application entry point
├── src/lcd_driver.c           # T-Display-S3 ST7789 i80 driver
├── src/lv_port_disp.c         # LVGL display port
├── src/desktop_widget.c       # Eight-page monitoring UI and motion
├── src/ikuai_monitor.c        # iKuai API, ping, and data cache
├── src/fonts/                 # D-DIN LVGL fonts
├── src/idf_component.yml      # Pinned LVGL 9.2.2 dependency
├── components/lv_conf.h       # Target-sized LVGL feature configuration
├── docs/                      # UI previews used above
└── platformio.ini             # t-display-s3 build entry
```

## Validation boundary

The host build has been checked with `pio run -e t-display-s3`. Display orientation, backlight, button input, Wi‑Fi, iKuai HTTPS, and real curve behavior still require a physical T-Display-S3. A successful upload alone is not hardware acceptance; this repository does not embed router credentials or claim physical-device validation.
