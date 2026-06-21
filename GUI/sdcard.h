#ifndef SDCARD_H
#define SDCARD_H

#include <sys/mount.h>
#include <lvgl/lvgl.h>

static int mount_sdcard(void);
static lv_font_t *load_font_from_sd(void);

extern lv_font_t *jp_font;

#endif