// LILYGO T-Display-S3 — ST7789 并口(i80)驱动（esp_lcd）
// 170x320 @ 8-bit i80；面板 BGR，开颜色反转；横屏 = swap_xy + mirror_x
//
// ⚠ 重点注意事项（来自 LILYGO 官方）：
// 1. GPIO15 是外设总电源，必须先置高，否则 LCD/背光都不工作
// 2. 该屏不是 SPI，是 8-bit 并口：D0-D7=39/40/41/42/45/46/47/48，WR=8，DC=7，CS=6，RST=5
// 3. 背光 GPIO38；整机 16MB Flash(QIO 80MHz) + 8MB OPI PSRAM（见 sdkconfig.defaults）
#include "lcd_driver.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"

static const char *TAG = "lcd";

#define PIN_PWR   15   // 外设总电源（必须先拉高！）
#define PIN_BL    38
#define PIN_RST   5
#define PIN_CS    6
#define PIN_DC    7
#define PIN_WR    8
// RD=GPIO9 不接（只写）
static const int s_data_pins[8] = { 39, 40, 41, 42, 45, 46, 47, 48 };

#define PCLK_HZ     (20 * 1000 * 1000)
#define BL_MAX_PCT  40    // 背光硬上限 40%（沿袭原项目约定）

// 170x320 面板在 240x320 GRAM 中的列偏移（竖屏坐标系，swap_xy 之前）
#define X_GAP 35
#define Y_GAP 0

static esp_lcd_panel_handle_t s_panel;

// ─── Backlight (LEDC PWM) ────────────────────────────────────────────

static void bl_init(void) {
    ledc_timer_config_t tmr = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&tmr);

    ledc_channel_config_t ch = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .gpio_num = PIN_BL,
        .duty = 0,
    };
    ledc_channel_config(&ch);
}

void lcd_set_backlight(uint8_t pct) {
    if (pct > BL_MAX_PCT) pct = BL_MAX_PCT;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (uint32_t)pct * 1023 / 100);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

// ─── 区域推送：i80 整块直推（无 SPI 分块限制）────────────────────────

void lcd_flush_area(int x0, int y0, int x1, int y1, const void *data) {
    esp_lcd_panel_draw_bitmap(s_panel, x0, y0, x1 + 1, y1 + 1, data);
}

// ─── Init ────────────────────────────────────────────────────────────

void lcd_init(void) {
    ESP_LOGI(TAG, "ST7789 i80 init (170x320)");

    // 1) 外设总电源：必须最先拉高（官方重点注意事项 #1）
    gpio_config_t pwr = {
        .pin_bit_mask = 1ULL << PIN_PWR,
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&pwr);
    gpio_set_level(PIN_PWR, 1);
    vTaskDelay(pdMS_TO_TICKS(50));

    // 2) i80 总线
    esp_lcd_i80_bus_handle_t i80_bus;
    esp_lcd_i80_bus_config_t bus_cfg = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .dc_gpio_num = PIN_DC,
        .wr_gpio_num = PIN_WR,
        .data_gpio_nums = {
            s_data_pins[0], s_data_pins[1], s_data_pins[2], s_data_pins[3],
            s_data_pins[4], s_data_pins[5], s_data_pins[6], s_data_pins[7],
        },
        .bus_width = 8,
        .max_transfer_bytes = LCD_W * 40 * sizeof(uint16_t) + 16,
        .psram_trans_align = 64,
        .sram_trans_align = 4,
    };
    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_cfg, &i80_bus));

    esp_lcd_panel_io_handle_t io;
    esp_lcd_panel_io_i80_config_t io_cfg = {
        .cs_gpio_num = PIN_CS,
        .pclk_hz = PCLK_HZ,
        .trans_queue_depth = 10,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_cfg, &io));

    // 3) ST7789 面板：BGR + 颜色反转 + 横屏(swap_xy + mirror_x) + GRAM 偏移
    esp_lcd_panel_dev_config_t panel_cfg = {
        .reset_gpio_num = PIN_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io, &panel_cfg, &s_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(s_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_init(s_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(s_panel, true));
    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(s_panel, X_GAP, Y_GAP));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(s_panel, true));   // 横屏 320x170
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(s_panel, true, false));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(s_panel, true));

    bl_init();
    ESP_LOGI(TAG, "LCD ready");
}
