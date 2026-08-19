// LILYGO T-Display-S3 — 桌面信息摆件（LVGL 界面）
// iKuai 路由器 WAN 状态 + 速率 + 趋势曲线；背光上限 40%
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lcd_driver.h"
#include "desktop_widget.h"
#include "config.h"

static const char *TAG = "main";

void app_main(void) {
    ESP_LOGI(TAG, "=== T-Display-S3 LVGL Widget ===");

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    lcd_init();
    lcd_set_backlight(APP_BL_PCT);          // 上限 40%（lcd_driver 内再 clamp）

    widget_start();

    while (1) vTaskDelay(pdMS_TO_TICKS(1000));
}
