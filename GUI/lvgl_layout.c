#include "lvgl.h"

void create_ui(void)
{
	lv_obj_t *scr = lv_screen_active();

	// root container
	lv_obj_t *root = lv_obj_create(scr);
	lv_obj_set_size(root, LV_PCT(100), LV_PCT(100));
	lv_obj_set_style_pad_all(root, 0, 0);
	lv_obj_set_flex_flow(root, LV_FLEX_FLOW_COLUMN);

	// top textbox
	lv_obj_t *search = lv_textarea_create(root);
	lv_obj_set_width(search, LV_PCT(100));
	lv_textarea_set_placeholder_text(search, "le searchbox");
	lv_obj_set_height(search, 40);

	// center area
	lv_obj_t *center = lv_obj_create(root);
	lv_obj_set_width(center, LV_PCT(100));
	lv_obj_set_flex_grow(center, 1);
	lv_obj_set_flex_flow(center, LV_FLEX_FLOW_ROW);

	lv_obj_t *left_list = lv_list_create(center);
	lv_obj_set_width(left_list, 100);
	lv_obj_set_height(left_list, LV_PCT(100));

	lv_list_add_button(left_list, NULL, "雨");
	lv_list_add_button(left_list, NULL, "飴");
	lv_list_add_button(left_list, NULL, "3");
	lv_list_add_button(left_list, NULL, "4");

	lv_obj_t *detail = lv_obj_create(center);
	lv_obj_set_flex_grow(detail, 1);
	lv_obj_set_height(detail, LV_PCT(100));

	lv_obj_t *detail_label = lv_label_create(detail);
	lv_label_set_text(detail_label,
		"Select an item\n"
		"from the list.");
	lv_obj_center(detail_label);

	// bottom options
	lv_obj_t *bottom = lv_obj_create(root);
	lv_obj_set_width(bottom, LV_PCT(100));
	lv_obj_set_height(bottom, 50);

	lv_obj_set_flex_flow(bottom, LV_FLEX_FLOW_ROW);

	lv_obj_t *btn;

	btn = lv_button_create(bottom);
	lv_label_set_text(lv_label_create(btn), "A");

	btn = lv_button_create(bottom);
	lv_label_set_text(lv_label_create(btn), "B");

	btn = lv_button_create(bottom);
	lv_label_set_text(lv_label_create(btn), "C");

	btn = lv_button_create(bottom);
	lv_label_set_text(lv_label_create(btn), "D");

	btn = lv_button_create(bottom);
	lv_label_set_text(lv_label_create(btn), "E");
}
