# Changelog / 变更日志

## 2026-08-21 — UI layout and physical-link validation

### 中文

- 修复 CPU/MEM 数值变化时 `%` 单位位置不随文本宽度更新的问题，避免单位漂移和重叠。
- 保留速率单位的动态宽度对齐，统一小屏上的数字、单位和胶囊标签基线。
- 更新中英文根 README 与固件 README：明确十页固件结构、UI SVG 预览、背光默认值和 15 FPS 曲线行为。
- 新增本次实机验证记录：固件成功编译并烧录到 T-Display-S3，8MB PSRAM 测试通过，Wi‑Fi 关联成功，真实 iKuai HTTPS API 返回成功，监控期间未观察到重启。
- 私有 Wi‑Fi、iKuai token、证书、串口路径和本地生成配置继续保持在 Git 之外。

### English

- Fixed CPU/MEM `%` suffix placement when the value width changes, preventing drift and overlap.
- Kept width-aware alignment for rate units so values, units, and capsule labels share a stable small-screen baseline.
- Updated the bilingual root README and firmware README with the ten-page structure, UI SVG previews, backlight defaults, and current 15 FPS curve behavior.
- Added physical validation evidence: the firmware built and flashed to a T-Display-S3, the 8 MB PSRAM test passed, Wi‑Fi associated, the live iKuai HTTPS API returned successfully, and no reboot was observed during the monitored run.
- Private Wi‑Fi settings, iKuai tokens, certificates, serial paths, and generated local configuration remain outside Git.

### Validation boundary / 验证边界

Build, serial, and API evidence confirm the firmware is running on the target board and can consume live telemetry. Final visual acceptance of every page—including display-angle readability and all transition states—still requires direct observation of the physical screen.
