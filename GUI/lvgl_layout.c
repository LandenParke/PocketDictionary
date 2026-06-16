#include "lvgl.h"

// screen size
int sx = 320;
int sy = 240;

// horz/vert seperations
int h1 = 40;
int h2 = 210;
int v1 = 40;


void create_ui(void)
{
	lv_obj_t *scr = lv_screen_active();


	// top search bar
	lv_obj_t *c1 = lv_obj_create(scr);
	lv_obj_set_pos(c1, 0, 0);
	lv_obj_set_size(c1, sx, h1);

	lv_obj_t *c1_label = lv_label_create(c1);
	lv_label_set_text(c1_label, "search");


	// left word list
	lv_obj_t *c2 = lv_obj_create(scr);
	lv_obj_set_pos(c2, 0, h1);
	lv_obj_set_size(c2, v1, sy-h1);


	// right details panel
	lv_obj_t *c3 = lv_obj_create(scr);
	lv_obj_set_pos(c3, v1, h1);
	lv_obj_set_size(c3, sx-v1, (sy-h1)-(sy-h2));


	// bottom options row
	lv_obj_t *c4 = lv_obj_create(scr);
	lv_obj_set_pos(c4, v1, h2);
	lv_obj_set_size(c4, sx-v1, sy-h2);


	// gen styling
	lv_obj_set_style_radius(c1, 0, 0);
	lv_obj_set_style_radius(c2, 0, 0);
	lv_obj_set_style_radius(c3, 0, 0);
	lv_obj_set_style_radius(c4, 0, 0);
	lv_obj_remove_flag(c1_label, LV_OBJ_FLAG_SCROLLABLE);

}
