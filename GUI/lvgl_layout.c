#include "lvgl.h"
extern lv_font_t jp_font_24;

// screen size
int sx = 320;
int sy = 240;
// horz/vert seperations
int h1 = 40;
int h2 = 210;
int v1 = 40;

int list_element_count = 4;


// lookup results placeholder
static const char *all_words[] = {
    "日", "一", "国", "人", "年", "大",
    "十", "二", "本", "中", "長", "出"
};
int results_count = (sizeof(all_words)/sizeof(all_words[0]));

static lv_obj_t *list_items[4];
static lv_obj_t *more_indicator;
static int sel_index = 0;
static int window_start = 0;

static void update_highlight(void)
{
    for (int i = 0; i < list_element_count; i++) {
        if (i == sel_index) {
            lv_obj_set_style_bg_color(list_items[i], lv_palette_main(LV_PALETTE_BLUE), 0);
            lv_obj_set_style_bg_opa(list_items[i], LV_OPA_COVER, 0);
        } else {
            lv_obj_set_style_bg_opa(list_items[i], LV_OPA_TRANSP, 0);
        }
    }
}

static void update_more_indicator(void)
{
    int last_visible_idx = window_start + list_element_count - 1;
    if (last_visible_idx < (int)results_count - 1) {
        lv_label_set_text(more_indicator, "...");
    } else {
        lv_label_set_text(more_indicator, "");
    }
}

static void populate_list(int start)
{
    window_start = start;
    for (int i = 0; i < list_element_count; i++) {
        int idx = start + i;
        lv_obj_t *label = lv_obj_get_child(list_items[i], 0);
        if (idx >= 0 && idx < (int)results_count) {
            lv_label_set_text(label, all_words[idx]);
        } else {
            lv_label_set_text(label, "");
        }
    }
    update_more_indicator();
}

static void keyboard_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_KEY) return;

    uint32_t key = lv_event_get_key(e);

    if (key == LV_KEY_DOWN) {
        if (sel_index < list_element_count - 1) {
            int next_idx = window_start + sel_index + 1;
            if (next_idx < (int)results_count) {
                sel_index++;
            }
        } else {
            if (window_start + list_element_count < (int)results_count) {
                populate_list(window_start + 1);
            }
        }
        update_highlight();
    } else if (key == LV_KEY_UP) {
        if (sel_index > 0) {
            sel_index--;
        } else {
            if (window_start > 0) {
                populate_list(window_start - 1);
            }
        }
        update_highlight();
    }
}

void create_ui(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

	// using 24px bitmap from noto sans CJK jp regular
    lv_obj_set_style_text_font(scr, &jp_font_24, 0);

    // top search bar
    lv_obj_t *c1 = lv_obj_create(scr);
    lv_obj_set_pos(c1, 0, 0);
    lv_obj_set_size(c1, sx, h1);
    lv_obj_remove_flag(c1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *c1_label = lv_label_create(c1);
    lv_label_set_text(c1_label, "search");

    // left word list
    lv_obj_t *c2 = lv_obj_create(scr);
    lv_obj_set_pos(c2, 0, h1);
    lv_obj_set_size(c2, v1, sy-h1);
    lv_obj_set_flex_flow(c2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(c2, 0, 0);
    lv_obj_set_style_pad_row(c2, 0, 0);
    lv_obj_remove_flag(c2, LV_OBJ_FLAG_SCROLLABLE);

    // list elements
    for (int i = 0; i < list_element_count; i++) {
        lv_obj_t *item = lv_obj_create(c2);
        lv_obj_set_size(item, v1, v1);
        lv_obj_set_style_radius(item, 0, 0);
        lv_obj_remove_flag(item, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_t *label = lv_label_create(item);
        lv_obj_center(label);
        lv_obj_remove_flag(label, LV_OBJ_FLAG_SCROLLABLE);
        list_items[i] = item;
    }

    // more indicator
    int squares_h = v1 * list_element_count;
    int remaining_h = (sy - h1) - squares_h;
    more_indicator = lv_label_create(c2);
    lv_obj_set_size(more_indicator, v1, remaining_h > 0 ? remaining_h : 0);
    lv_obj_set_style_text_align(more_indicator, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_remove_flag(more_indicator, LV_OBJ_FLAG_SCROLLABLE);

    populate_list(0);
    update_highlight();

    // right details panel
    lv_obj_t *c3 = lv_obj_create(scr);
    lv_obj_set_pos(c3, v1, h1);
    lv_obj_set_size(c3, sx-v1, (sy-h1)-(sy-h2));
    lv_obj_remove_flag(c3, LV_OBJ_FLAG_SCROLLABLE);

    // bottom options row
    lv_obj_t *c4 = lv_obj_create(scr);
    lv_obj_set_pos(c4, v1, h2);
    lv_obj_set_size(c4, sx-v1, sy-h2);
    lv_obj_remove_flag(c4, LV_OBJ_FLAG_SCROLLABLE);

    // gen styling
    lv_obj_set_style_radius(c1, 0, 0);
    lv_obj_set_style_radius(c2, 0, 0);
    lv_obj_set_style_radius(c3, 0, 0);
    lv_obj_set_style_radius(c4, 0, 0);
    lv_obj_remove_flag(c1_label, LV_OBJ_FLAG_SCROLLABLE);

    // word list navigation
    lv_group_t *g = lv_group_get_default();
    if (!g) {
        g = lv_group_create();
        lv_group_set_default(g);
    }
    lv_group_add_obj(g, c2);
    lv_obj_add_event_cb(c2, keyboard_event_cb, LV_EVENT_KEY, NULL);
    lv_group_focus_obj(c2);
}
