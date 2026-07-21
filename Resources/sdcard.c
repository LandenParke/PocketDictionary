#include <sys/mount.h>
#include <lvgl/lvgl.h>



static int mount_sdcard(void) {
    int res = mount("/dev/mmcsd0", "/mnt", "vfat", 0, NULL);
    if (res < 0) {
        perror("Can't mount SD card");
        return res;
    }
    return 1;
}

static lv_font_t *jp_font = NULL;

static lv_font_t *load_font_from_sd(void) {
    lv_font_t *font = lv_binfont_create("S:jp_font.bin");
    if (font == NULL) {
        LV_LOG_ERROR("Can't load SD Card");
    }
    return font;
}

