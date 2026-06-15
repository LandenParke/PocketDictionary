#include "lvgl.h"


void create_ui(void)
{


	lv_obj_t *scr = lv_screen_active();

	lv_obj_t *r1 = lv_obj_create(scr);
	lv_obj_set_pos(r1, 0, 0);
	lv_obj_set_size(r1, 320, 40);

	lv_obj_t *r2 = lv_obj_create(scr);
	lv_obj_set_pos(r2, 0, 40);
	lv_obj_set_size(r2, 60, 200);

	lv_obj_t *r3 = lv_obj_create(scr);
	lv_obj_set_pos(r3, 60, 40);
	lv_obj_set_size(r3, 260, 170);

	lv_obj_t *r4 = lv_obj_create(scr);
	lv_obj_set_pos(r4, 60, 210);
	lv_obj_set_size(r4, 260, 30);


}
