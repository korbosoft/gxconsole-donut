#ifndef GX_CONSOLE_H
#define GX_CONSOLE_H

#include <gccore.h>
#include <sys/iosupport.h>

#include "console_internal.h"

#define _ANSI_MAXARGS 16

typedef struct gx_console_font_t {
    u8 char_width;
    u8 char_height;
    u8 bpp;
    u8 ascii_offset;
    u16 num_chars;
    const u8 *pixels;
} GxConsoleFont;

typedef struct
{
    struct
    {
        int flags;
        u16 fg;
        u16 bg;
    } color;
    int arg_idx;
    int args[_ANSI_MAXARGS];
    int color_arg_count;
    unsigned int color_args[3];
    bool has_arg;
    enum
    {
        ESC_NONE,
        ESC_START,
        ESC_BUILDING_UNKNOWN,
        ESC_BUILDING_FORMAT_FG,
        ESC_BUILDING_FORMAT_BG,
        ESC_BUILDING_FORMAT_FG_NONRGB,
        ESC_BUILDING_FORMAT_BG_NONRGB,
        ESC_BUILDING_FORMAT_FG_RGB,
        ESC_BUILDING_FORMAT_BG_RGB,
    } state;
} EscapeSeq;

typedef struct gx_console_t {
    GXTexObj texobj;
    u16 width_chars;
    u16 height_chars;
    u32 texture_size;
    const GxConsoleFont *font;
    u8 char_w;
    u8 char_h;
    u16 pitch;
    u16 tiles_per_row; /* GX 4x4 tiles in a row */
    u16 bg;
    u16 fg;
    int flags;
    u8 tab_size;
    u8 alpha;
    u16 cursor_x;
    u16 cursor_y;
    u16 prev_cursor_x;
    u16 prev_cursor_y;
    EscapeSeq esc;
    devoptab_t dotab;
    u8 texels[] ATTRIBUTE_ALIGN(32);
} GxConsole;

GxConsole *gx_console_new(u16 width_chars, u16 height_chars,
                          const GxConsoleFont *font);
void gx_console_get_cursor_pos(GxConsole *console, int *row, int *column);
void gx_console_set_input(GxConsole *console, int fd);
void gx_console_set_alpha(GxConsole *console, u8 alpha);
void gx_console_draw(GxConsole *console, int x, int y);
GXTexObj *gx_console_get_texobj(GxConsole *console);

const GxConsoleFont *gx_console_font_default();

extern const GxConsoleFont font_tamzen_8x15;
extern const GxConsoleFont font_cozette_6x13;

#define CONSOLE_BLACK   CONSOLE_ESC(30m)
#define CONSOLE_RED     CONSOLE_ESC(31;1m)
#define CONSOLE_GREEN   CONSOLE_ESC(32;1m)
#define CONSOLE_YELLOW  CONSOLE_ESC(33;1m)
#define CONSOLE_BLUE    CONSOLE_ESC(34;1m)
#define CONSOLE_MAGENTA CONSOLE_ESC(35;1m)
#define CONSOLE_CYAN    CONSOLE_ESC(36;1m)
#define CONSOLE_WHITE   CONSOLE_ESC(37;1m)

#define CONSOLE_BG_BLACK   CONSOLE_ESC(40m)
#define CONSOLE_BG_RED     CONSOLE_ESC(41;1m)
#define CONSOLE_BG_GREEN   CONSOLE_ESC(42;1m)
#define CONSOLE_BG_YELLOW  CONSOLE_ESC(43;1m)
#define CONSOLE_BG_BLUE    CONSOLE_ESC(44;1m)
#define CONSOLE_BG_MAGENTA CONSOLE_ESC(45;1m)
#define CONSOLE_BG_CYAN    CONSOLE_ESC(46;1m)
#define CONSOLE_BG_WHITE   CONSOLE_ESC(47;1m)

#define CONSOLE_COLOR_BLACK   0
#define CONSOLE_COLOR_RED     1
#define CONSOLE_COLOR_GREEN   2
#define CONSOLE_COLOR_YELLOW  3
#define CONSOLE_COLOR_BLUE    4
#define CONSOLE_COLOR_MAGENTA 5
#define CONSOLE_COLOR_CYAN    6
#define CONSOLE_COLOR_WHITE   7

#endif /* GX_CONSOLE_H */
