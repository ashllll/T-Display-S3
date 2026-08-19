/*******************************************************************************
 * Size: 12 px
 * Bpp: 2
 * Opts: --no-compress --no-prefilter --bpp 2 --size 12 --font /mnt/agents/D-DIN.ttf -r 0x20-0x7E --format lvgl -o ui_font_ddin_12.c --force-fast-kern-format
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef UI_FONT_DDIN_12
#define UI_FONT_DDIN_12 1
#endif

#if UI_FONT_DDIN_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x33, 0x33, 0x22, 0x3,

    /* U+0022 "\"" */
    0x58, 0x58, 0x18,

    /* U+0023 "#" */
    0x8, 0x80, 0x48, 0x7e, 0xe1, 0x8, 0x20, 0x87,
    0xbd, 0x21, 0x42, 0x20,

    /* U+0024 "$" */
    0x4, 0x3, 0x43, 0xe9, 0x61, 0x7c, 0x7, 0xd0,
    0x8d, 0x63, 0x2e, 0x42, 0x0,

    /* U+0025 "%" */
    0x3c, 0x5, 0x5, 0x50, 0x80, 0x95, 0x20, 0x5,
    0x52, 0x28, 0x28, 0x85, 0x50, 0x8, 0x55, 0x2,
    0x5, 0x50, 0x50, 0x2c,

    /* U+0026 "&" */
    0xf, 0x40, 0x82, 0x1, 0x54, 0x3, 0x80, 0x2b,
    0x0, 0x86, 0xc2, 0xd, 0xa, 0x99,

    /* U+0027 "'" */
    0x55, 0x10,

    /* U+0028 "(" */
    0x4, 0x52, 0x8, 0x21, 0x82, 0xc, 0x20, 0x10,

    /* U+0029 ")" */
    0x0, 0x81, 0x42, 0x8, 0x20, 0x85, 0x20, 0x80,

    /* U+002A "*" */
    0x8, 0x2c, 0x19, 0x0,

    /* U+002B "+" */
    0x1, 0x0, 0x50, 0x3f, 0xd0, 0x50, 0x5, 0x0,

    /* U+002C "," */
    0x55, 0x0,

    /* U+002D "-" */
    0x3f, 0x0,

    /* U+002E "." */
    0x6,

    /* U+002F "/" */
    0x2, 0x2, 0x8, 0x8, 0x8, 0x10, 0x20, 0x20,

    /* U+0030 "0" */
    0x1f, 0x43, 0xc, 0x20, 0xc2, 0xc, 0x20, 0xc2,
    0xc, 0x30, 0xc1, 0xf4,

    /* U+0031 "1" */
    0x2d, 0x70, 0xc3, 0xc, 0x30, 0xc3,

    /* U+0032 "2" */
    0x2f, 0x8, 0x30, 0xc, 0x9, 0x3, 0x3, 0x2,
    0x41, 0xfe,

    /* U+0033 "3" */
    0x2f, 0x42, 0xc, 0x0, 0xc0, 0x74, 0x0, 0xc0,
    0xc, 0x30, 0xc2, 0xf4,

    /* U+0034 "4" */
    0x2, 0x0, 0x90, 0xc, 0x1, 0x44, 0x31, 0x82,
    0x18, 0x7f, 0xd0, 0x18,

    /* U+0035 "5" */
    0x3f, 0x82, 0x0, 0x20, 0x3, 0xb4, 0x20, 0xc0,
    0xc, 0x20, 0xc2, 0xf4,

    /* U+0036 "6" */
    0x3, 0x0, 0x80, 0x8, 0x2, 0xf4, 0x30, 0xc6,
    0x8, 0x30, 0xc1, 0xf4,

    /* U+0037 "7" */
    0x7f, 0x80, 0x50, 0x30, 0x8, 0x9, 0x3, 0x1,
    0x80, 0x80,

    /* U+0038 "8" */
    0x1f, 0x43, 0xc, 0x30, 0xc1, 0xf4, 0x30, 0xc2,
    0x9, 0x30, 0xc1, 0xf4,

    /* U+0039 "9" */
    0x1f, 0x43, 0xc, 0x60, 0x83, 0xc, 0x1f, 0x80,
    0x30, 0x6, 0x0, 0xc0,

    /* U+003A ":" */
    0x60, 0x0, 0x60,

    /* U+003B ";" */
    0x60, 0x0, 0x22, 0x10,

    /* U+003C "<" */
    0x0, 0x0, 0x68, 0x38, 0x1, 0xe0, 0x0, 0x90,
    0x0,

    /* U+003D "=" */
    0x3f, 0xd0, 0x0, 0x3f, 0xd0,

    /* U+003E ">" */
    0x0, 0x2, 0x90, 0x1, 0xd0, 0xb8, 0x64, 0x0,
    0x0,

    /* U+003F "?" */
    0x2e, 0x14, 0x50, 0x14, 0xc, 0x8, 0x3, 0x0,
    0x0, 0x30,

    /* U+0040 "@" */
    0x2, 0xed, 0x0, 0xc0, 0x18, 0x30, 0xec, 0x92,
    0x20, 0xc2, 0x63, 0x8, 0x26, 0x30, 0x82, 0x22,
    0x4c, 0x63, 0xa, 0x68, 0xc, 0x0, 0x0, 0x2f,
    0xe0,

    /* U+0041 "A" */
    0x3, 0x0, 0x19, 0x0, 0xc8, 0x2, 0x20, 0x20,
    0x60, 0xea, 0xc5, 0x2, 0x60, 0x2,

    /* U+0042 "B" */
    0x3f, 0xe0, 0xc0, 0x93, 0x2, 0x4f, 0xf8, 0x30,
    0x24, 0xc0, 0x63, 0x2, 0x4f, 0xf8,

    /* U+0043 "C" */
    0xb, 0xd0, 0xc0, 0x92, 0x0, 0x8, 0x0, 0x20,
    0x0, 0x80, 0x3, 0x2, 0x42, 0xf4,

    /* U+0044 "D" */
    0x3f, 0xd0, 0xc0, 0x93, 0x1, 0x8c, 0x2, 0x30,
    0x8, 0xc0, 0x63, 0x2, 0x4f, 0xf4,

    /* U+0045 "E" */
    0x3f, 0xf3, 0x0, 0x30, 0x3, 0xfd, 0x30, 0x3,
    0x0, 0x30, 0x3, 0xff,

    /* U+0046 "F" */
    0x3f, 0xf3, 0x0, 0x30, 0x3, 0xfd, 0x30, 0x3,
    0x0, 0x30, 0x3, 0x0,

    /* U+0047 "G" */
    0xb, 0xd0, 0xc0, 0x92, 0x0, 0x8, 0x0, 0x20,
    0xb4, 0x80, 0x53, 0x2, 0x42, 0xf4,

    /* U+0048 "H" */
    0x30, 0x18, 0xc0, 0x63, 0x1, 0x8f, 0xfe, 0x30,
    0x18, 0xc0, 0x63, 0x1, 0x8c, 0x6,

    /* U+0049 "I" */
    0xff, 0xff,

    /* U+004A "J" */
    0x8, 0x20, 0x82, 0x8, 0x20, 0x9d,

    /* U+004B "K" */
    0x30, 0x24, 0x30, 0x90, 0x31, 0x80, 0x33, 0x40,
    0x3c, 0xc0, 0x30, 0x60, 0x30, 0x30, 0x30, 0xc,

    /* U+004C "L" */
    0x30, 0x3, 0x0, 0x30, 0x3, 0x0, 0x30, 0x3,
    0x0, 0x30, 0x3, 0xfe,

    /* U+004D "M" */
    0x30, 0x3, 0xe, 0x2, 0xc3, 0x80, 0xf0, 0xd8,
    0x9c, 0x32, 0x33, 0xc, 0x74, 0xc3, 0x4, 0x30,
    0xc0, 0xc,

    /* U+004E "N" */
    0x30, 0xc, 0xf0, 0x33, 0xa0, 0xcc, 0xc3, 0x30,
    0xcc, 0xc2, 0xb3, 0x3, 0xcc, 0x3,

    /* U+004F "O" */
    0xb, 0xd0, 0xc0, 0xc2, 0x1, 0x48, 0x6, 0x20,
    0x18, 0x80, 0x53, 0x3, 0x2, 0xf4,

    /* U+0050 "P" */
    0x3f, 0xe0, 0xc0, 0x93, 0x1, 0x8c, 0x9, 0x3f,
    0xd0, 0xc0, 0x3, 0x0, 0xc, 0x0,

    /* U+0051 "Q" */
    0xb, 0xd0, 0xc0, 0xc2, 0x1, 0x48, 0x6, 0x20,
    0x18, 0x80, 0x53, 0x3, 0x2, 0xf8, 0x0, 0x60,
    0x0, 0x40,

    /* U+0052 "R" */
    0x3f, 0xe0, 0xc0, 0x93, 0x1, 0x4c, 0x9, 0x3a,
    0xd0, 0xc3, 0x3, 0x3, 0xc, 0x9,

    /* U+0053 "S" */
    0x1e, 0x86, 0x6, 0x60, 0x3, 0x90, 0x1, 0x90,
    0x3, 0x60, 0x32, 0xe8,

    /* U+0054 "T" */
    0xbf, 0xe0, 0x90, 0x9, 0x0, 0x90, 0x9, 0x0,
    0x90, 0x9, 0x0, 0x90,

    /* U+0055 "U" */
    0x30, 0x8, 0xc0, 0x23, 0x0, 0x8c, 0x2, 0x30,
    0x8, 0xc0, 0x63, 0x42, 0x42, 0xf4,

    /* U+0056 "V" */
    0xc0, 0x31, 0x40, 0x83, 0x9, 0x8, 0x30, 0x14,
    0x80, 0x35, 0x0, 0xb0, 0x1, 0x80,

    /* U+0057 "W" */
    0xc0, 0xd0, 0x59, 0xe, 0x8, 0x61, 0x70, 0xc3,
    0x22, 0x8, 0x23, 0x15, 0x41, 0x60, 0xa0, 0xd,
    0xe, 0x0, 0xc0, 0xa0,

    /* U+0058 "X" */
    0x60, 0x30, 0x92, 0x40, 0xd8, 0x1, 0xc0, 0xb,
    0x40, 0x23, 0x3, 0x6, 0x24, 0x9,

    /* U+0059 "Y" */
    0x90, 0x63, 0xc, 0x25, 0x80, 0xf0, 0xa, 0x0,
    0x50, 0x5, 0x0, 0x50,

    /* U+005A "Z" */
    0x7f, 0xe0, 0x8, 0x1, 0x80, 0x30, 0x9, 0x1,
    0x80, 0x30, 0x7, 0xfe,

    /* U+005B "[" */
    0x38, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xe0,

    /* U+005C "\\" */
    0x20, 0x20, 0x10, 0x8, 0x8, 0x8, 0x2, 0x2,

    /* U+005D "]" */
    0x38, 0x61, 0x86, 0x18, 0x61, 0x86, 0x18, 0xe0,

    /* U+005E "^" */
    0x1, 0x0, 0xa0, 0x5, 0x42, 0x8, 0x20, 0x50,

    /* U+005F "_" */
    0xaa, 0x90,

    /* U+0060 "`" */
    0x10, 0x60,

    /* U+0061 "a" */
    0x2a, 0x41, 0xc, 0x1a, 0xc6, 0xc, 0x50, 0xc2,
    0xac,

    /* U+0062 "b" */
    0x20, 0x2, 0x0, 0x3b, 0x83, 0x9, 0x20, 0x52,
    0x5, 0x30, 0x93, 0xa8,

    /* U+0063 "c" */
    0x1e, 0x82, 0x8, 0x60, 0x6, 0x0, 0x20, 0x81,
    0xa8,

    /* U+0064 "d" */
    0x0, 0x80, 0x8, 0x2e, 0x82, 0xc, 0x60, 0x86,
    0x8, 0x20, 0xc2, 0xac,

    /* U+0065 "e" */
    0x1a, 0x82, 0x8, 0x7a, 0x96, 0x0, 0x30, 0x81,
    0xe8,

    /* U+0066 "f" */
    0x1d, 0x20, 0x79, 0x20, 0x20, 0x20, 0x20, 0x20,

    /* U+0067 "g" */
    0x2e, 0x82, 0xc, 0x60, 0x86, 0x8, 0x30, 0xc1,
    0xa8, 0x10, 0x82, 0xe4,

    /* U+0068 "h" */
    0x20, 0x2, 0x0, 0x3b, 0x83, 0x9, 0x20, 0x52,
    0x5, 0x20, 0x52, 0x5,

    /* U+0069 "i" */
    0x30, 0x33, 0x33, 0x33,

    /* U+006A "j" */
    0x8, 0x0, 0x82, 0x8, 0x20, 0x82, 0x9, 0xd0,

    /* U+006B "k" */
    0x20, 0x2, 0x0, 0x20, 0xc2, 0x20, 0x2a, 0x3,
    0x70, 0x20, 0xc2, 0x9,

    /* U+006C "l" */
    0x20, 0x82, 0x8, 0x20, 0x83, 0xa,

    /* U+006D "m" */
    0x3a, 0x9b, 0x4c, 0x28, 0x32, 0x5, 0xc, 0x81,
    0x43, 0x20, 0x50, 0xc8, 0x14, 0x30,

    /* U+006E "n" */
    0x3a, 0x83, 0x9, 0x20, 0x52, 0x5, 0x20, 0x52,
    0x5,

    /* U+006F "o" */
    0x1f, 0x82, 0x8, 0x60, 0x56, 0x5, 0x20, 0x81,
    0xa8,

    /* U+0070 "p" */
    0x3a, 0x83, 0x9, 0x20, 0x52, 0x5, 0x30, 0x93,
    0xa8, 0x20, 0x2, 0x0,

    /* U+0071 "q" */
    0x2e, 0x82, 0xc, 0x60, 0x86, 0x8, 0x20, 0xc2,
    0xa8, 0x0, 0x80, 0x8,

    /* U+0072 "r" */
    0x0, 0x3a, 0x30, 0x20, 0x20, 0x20, 0x20,

    /* U+0073 "s" */
    0x2a, 0x46, 0x8, 0x35, 0x0, 0x18, 0x50, 0xc2,
    0xa4,

    /* U+0074 "t" */
    0x10, 0x20, 0x79, 0x20, 0x20, 0x20, 0x20, 0x1d,

    /* U+0075 "u" */
    0x20, 0x52, 0x5, 0x20, 0x52, 0x5, 0x30, 0x81,
    0xe8,

    /* U+0076 "v" */
    0x80, 0xc6, 0x18, 0x32, 0x2, 0x30, 0x1e, 0x0,
    0xc0,

    /* U+0077 "w" */
    0x80, 0xc2, 0x14, 0xb0, 0xc3, 0x25, 0x20, 0x88,
    0x94, 0x1c, 0x2c, 0x3, 0x6, 0x0,

    /* U+0078 "x" */
    0x51, 0x48, 0x80, 0xc0, 0x74, 0x33, 0x24, 0x60,

    /* U+0079 "y" */
    0x80, 0xc6, 0x8, 0x32, 0x2, 0x30, 0x1a, 0x0,
    0xc0, 0xc, 0x3, 0x40,

    /* U+007A "z" */
    0x3f, 0x80, 0x90, 0x60, 0x30, 0x20, 0x1e, 0xa0,

    /* U+007B "{" */
    0x9, 0x14, 0x14, 0x14, 0x24, 0x30, 0x24, 0x14,
    0x14, 0xd,

    /* U+007C "|" */
    0x48, 0x88, 0x88, 0x88, 0x88,

    /* U+007D "}" */
    0x20, 0x18, 0x18, 0x18, 0x18, 0xd, 0x18, 0x18,
    0x18, 0x30,

    /* U+007E "~" */
    0x28, 0x11, 0x28
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 42, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 46, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 59, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 7, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 88, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 32, .adv_w = 159, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 33, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 68, .adv_w = 55, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 55, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 84, .adv_w = 72, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 88, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 96, .adv_w = 33, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 98, .adv_w = 75, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 100, .adv_w = 37, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 75, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 63, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 90, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 93, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 83, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 37, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 37, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 226, .adv_w = 98, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 98, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 240, .adv_w = 98, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 82, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 167, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 284, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 105, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 48, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 60, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 115, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 145, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 506, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 105, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 93, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 100, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 153, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 57, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 638, .adv_w = 75, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 57, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 654, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 662, .adv_w = 88, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 664, .adv_w = 96, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 666, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 696, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 63, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 737, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 45, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 43, .box_w = 3, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 761, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 158, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 823, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 835, .adv_w = 65, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 842, .adv_w = 89, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 65, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 84, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 137, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 899, .adv_w = 84, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 911, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 65, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 929, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 934, .adv_w = 65, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 944, .adv_w = 98, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 2, 0, 3, 4, 5, 0, 6,
    7, 4, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 8, 0, 0, 9, 10,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 11, 12, 13, 0, 0,
    0, 0, 0, 14, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    15, 0, 0, 16, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 2, 0, 2,
    3, 4, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 6, 0, 7,
    8, 0, 9, 0, 0, 0, 0, 0,
    0, 0, 10, 11, 12, 12, 12, 0,
    13, 11, 14, 15, 11, 11, 11, 11,
    12, 11, 12, 11, 0, 0, 11, 16,
    16, 0, 16, 17, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, -13, -7, -6,
    -13, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, -8,
    0, -2, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, -2, -1, -2, -2, -1,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    -7, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 16,
    .right_class_cnt     = 17,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_ddin_12 = {
#else
lv_font_t ui_font_ddin_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_DDIN_12*/

