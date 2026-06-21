/****************************************************************************
 * apps/examples/lvgldemo/lvgldemo.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <nuttx/config.h>
#include <unistd.h>
#include <sys/boardctl.h>

#include <lvgl/lvgl.h>





#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <jp_font_24.c>
void create_ui(void);



#include <lvgl/demos/lv_demos.h>
#ifdef CONFIG_LV_USE_NUTTX_LIBUV
#include <uv.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * KEYPAD INPUT
 ****************************************************************************/

static lv_indev_t *kb_indev;

static uint32_t g_last_key;
static bool g_key_pressed;

#ifndef CONFIG_ARCH_BOARD_SPRESENSE

static void set_stdin_nonblock(void)
{
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

static struct termios oldt;
static void enable_raw_mode(void)
{
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

static void poll_keyboard(void)
{
  char c;
  int n;

  n = read(STDIN_FILENO, &c, 1);

  if (n <= 0)
    {
      g_key_pressed = false;
      return;
    }

  switch (c)
    {
      case 'w':
        g_last_key = LV_KEY_UP;
        g_key_pressed = true;
        break;

      case 's':
        g_last_key = LV_KEY_DOWN;
        g_key_pressed = true;
        break;

      case 'a':
        g_last_key = LV_KEY_LEFT;
        g_key_pressed = true;
        break;

      case 'r':
        g_last_key = LV_KEY_RIGHT;
        g_key_pressed = true;
        break;

      case '\r':
      case '\n':
        g_last_key = LV_KEY_ENTER;
        g_key_pressed = true;
        break;

      default:
        g_key_pressed = false;
        break;
    }

  if (g_key_pressed)
    {
      printf("LVGL key=%lu\n", (unsigned long)g_last_key);
      fflush(stdout);
    }
}

#else



// spresense buttons placeholder
static void poll_buttons(void)
{
	if (btn_up_pressed())
		{
		g_last_key = LV_KEY_UP;
		g_key_pressed = true;
		}
	else if (btn_down_pressed())
		{
		g_last_key = LV_KEY_DOWN;
		g_key_pressed = true;
		}
	else if (btn_left_pressed())
		{
		g_last_key = LV_KEY_LEFT;
		g_key_pressed = true;
		}
	else if (btn_right_pressed())
		{
		g_last_key = LV_KEY_RIGHT;
		g_key_pressed = true;
		}
	else if (btn_ok_pressed())
		{
		g_last_key = LV_KEY_ENTER;
		g_key_pressed = true;
		}

	if (g_key_pressed)
		{
		printf("LVGL key=%lu\n", (unsigned long)g_last_key);
		fflush(stdout);
		}
}

#endif

static void keypad_read_cb(lv_indev_t *indev,
                           lv_indev_data_t *data) 
{
	#ifndef CONFIG_ARCH_BOARD_SPRESENSE
	poll_keyboard();
	#else
	poll_buttons();
	#endif

	if (g_key_pressed)
		{
		data->key = g_last_key;
		data->state = LV_INDEV_STATE_PRESSED;
		}
	else
		{
		data->state = LV_INDEV_STATE_RELEASED;
		}
}




/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_LV_USE_NUTTX_LIBUV
static void lv_nuttx_uv_loop(uv_loop_t *loop, lv_nuttx_result_t *result)
{
  lv_nuttx_uv_t uv_info;
  void *data;

  uv_loop_init(loop);

  lv_memset(&uv_info, 0, sizeof(uv_info));
  uv_info.loop = loop;
  uv_info.disp = result->disp;
  uv_info.indev = result->indev;
#ifdef CONFIG_UINPUT_TOUCH
  uv_info.uindev = result->utouch_indev;
#endif

  data = lv_nuttx_uv_init(&uv_info);
  uv_run(loop, UV_RUN_DEFAULT);
  lv_nuttx_uv_deinit(&data);
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: main or lv_demos_main
 *
 * Description:
 *
 * Input Parameters:
 *   Standard argc and argv
 *
 * Returned Value:
 *   Zero on success; a positive, non-zero value on failure.
 *
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{
  lv_nuttx_dsc_t info;
  lv_nuttx_result_t result;

#ifdef CONFIG_LV_USE_NUTTX_LIBUV
  uv_loop_t ui_loop;
  lv_memzero(&ui_loop, sizeof(ui_loop));
#endif

  if (lv_is_initialized())
    {
      LV_LOG_ERROR("LVGL already initialized! aborting.");
      return -1;
    }

  lv_init();

  lv_nuttx_dsc_init(&info);

#ifdef CONFIG_LV_USE_NUTTX_LCD
  info.fb_path = "/dev/lcd0";
#endif

#ifdef CONFIG_INPUT_TOUCHSCREEN
  info.input_path = CONFIG_EXAMPLES_LVGLDEMO_INPUT_DEVPATH;
#endif

  lv_nuttx_init(&info, &result);

  if (result.disp == NULL)
    {
      LV_LOG_ERROR("lv_demos initialization failure!");
      return 1;
    }


	// input
	#ifndef CONFIG_ARCH_BOARD_SPRESENSE
	enable_raw_mode();
	set_stdin_nonblock();
	#endif
	kb_indev = lv_indev_create();
	lv_indev_set_type(kb_indev, LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_read_cb(kb_indev, keypad_read_cb);

	create_ui();


#ifdef CONFIG_LV_USE_NUTTX_LIBUV
  lv_nuttx_uv_loop(&ui_loop, &result);
#else
  while (1)
    {
      uint32_t idle;
      idle = lv_timer_handler();

      /* Minimum sleep of 1ms */

      idle = idle ? idle : 1;
      usleep(idle * 1000);
    }
#endif


}













/****************************************************************************
 * LAYOUT
 ****************************************************************************/




// screen size
int sx = 320;
int sy = 240;
// horz/vert seperations
int h1 = 40;
int h2 = 210;
int v1 = 40;


// lookup results
// fill more elements + format later
typedef struct {
    const char *word;
	const char *accent;
    const char *detail;
} dict_entry;
// word + details
static const dict_entry entries[] = {
    {"器官", " common | JLPT N1", "1. organ (noun)"},
    {"期間", " common | JLPT N3", "1. period (noun)\n2. interval (noun)"},
    {"機関", " common | JLPT N3", "1. institution (noun)"},
    {"帰還", " common", "1. return (noun)\n2. feedback (noun)"},
    {"旗艦", "", "1. flagship (noun)"},
    {"季刊", " common | JLPT N1", "1. quarterly (noun)"}
};
static const int results_count = sizeof(entries) / sizeof(entries[0]);


// word list
#define list_element_count 6
static lv_obj_t *list_items[list_element_count];
static int window_start = 0;


// bottom bar
#define BOTTOM_ITEM_COUNT 4
static lv_obj_t *bottom_items[BOTTOM_ITEM_COUNT];
static int bottom_sel_index = 0;
static void update_bottom_highlight(void) {
	for (int i = 0; i < BOTTOM_ITEM_COUNT; i++) {
		if (i == bottom_sel_index) {
			lv_obj_set_style_bg_color(bottom_items[i], lv_color_hex(0xF58E27), 0);
			lv_obj_set_style_bg_opa(bottom_items[i], LV_OPA_COVER, 0);
		} else {
			lv_obj_set_style_bg_opa(bottom_items[i], LV_OPA_TRANSP, 0);
		}
	}
}
static lv_obj_t *bottom_labels[BOTTOM_ITEM_COUNT];
static void update_results(void) {
	lv_label_set_text_fmt(bottom_labels[0], "%d found", results_count);
}


static lv_obj_t *selected_label;
static lv_obj_t *accent_label;
static lv_obj_t *details_label;
static void populate_list(int start)
{
    window_start = start;
    lv_label_set_text(selected_label, entries[start].word);
	lv_label_set_text(accent_label, entries[start].accent);
    lv_label_set_text(details_label, entries[start].detail);

    for (int i = 1; i < list_element_count; i++){
		lv_obj_t *label = lv_obj_get_child(list_items[i], 0);
        int idx = start + i;
        if (idx < results_count) {
			lv_label_set_text(label, entries[idx].word);
		} else {
			lv_label_set_text(label, "");
		}
    }
}


static lv_group_t *g;

static void keyboard_event_cb(lv_event_t *e);
static lv_obj_t *search;
static lv_obj_t *kb = NULL;
void osc_keyboard(void)
{
	if (kb) {
		lv_obj_del(kb);
		kb = NULL;
		return;
	}

	kb = lv_keyboard_create(lv_layer_top());
	lv_obj_set_size(kb, LV_PCT(100), LV_PCT(50));
	lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);

	lv_keyboard_set_textarea(kb, search);

	lv_group_add_obj(g, search);
	lv_group_focus_obj(search);
	lv_obj_add_event_cb(kb, keyboard_event_cb, LV_EVENT_ALL, NULL);
}

lv_obj_t *list;
static void keyboard_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	uint32_t key = lv_event_get_key(e);

	if (key == LV_KEY_DOWN)
	{
		if (window_start < results_count - 1)
		{
			populate_list(window_start + 1);
		}
	}
	if (key == LV_KEY_UP)
	{
		if (window_start > 0)
		{
			populate_list(window_start - 1);
		}
	}
	if (key == LV_KEY_LEFT) {
		if (bottom_sel_index > 0) {
			bottom_sel_index--;
			update_bottom_highlight();
		}
	}
	if (key == LV_KEY_RIGHT) {
		if (bottom_sel_index < BOTTOM_ITEM_COUNT - 1) {
			bottom_sel_index++;
			update_bottom_highlight();
		}

	}
	if (key == LV_KEY_ENTER) {
		int word_idx = window_start;
		if (word_idx < results_count) {
			printf("word=%s  option=%d\n", entries[word_idx].word, bottom_sel_index);
			fflush(stdout);
		}
		if (bottom_sel_index == 1) {
			osc_keyboard();
		}
	}

	// on screen keyboard
	if (code == LV_EVENT_READY) {
		// enter/submit
		printf("search text submitted: %s\n", lv_textarea_get_text(search));

		lv_obj_del(kb);
		kb = NULL;
		lv_group_focus_obj(list);
	}
	else if (code == LV_EVENT_CANCEL) {
		lv_obj_del(kb);
		kb = NULL;
		lv_group_focus_obj(list);
	}
}



void create_ui(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

	// using 24px bitmap from noto sans CJK jp regular
    lv_obj_set_style_text_font(scr, &jp_font_24, 0);

	// root
	lv_obj_t *root = lv_obj_create(scr);
	lv_obj_set_size(root, LV_PCT(100), LV_PCT(100));
	lv_obj_set_flex_flow(root, LV_FLEX_FLOW_COLUMN);
	

    // top search bar
	search = lv_textarea_create(root);
	lv_obj_set_style_text_font(search, &lv_font_montserrat_14, 0);
	lv_obj_set_width(search, LV_PCT(100));
	lv_obj_set_height(search, 30);


	// selected word
	lv_obj_t *selected = lv_obj_create(root);
	lv_obj_set_width(selected, LV_PCT(100));
	lv_obj_set_height(selected, 30);
	lv_obj_set_flex_flow(selected, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(selected, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	// word
	selected_label = lv_label_create(selected);
	lv_obj_set_style_text_color(selected_label, lv_color_hex(0xF58E27), 0);
	lv_obj_set_width(selected_label, LV_SIZE_CONTENT);
	lv_obj_set_pos(selected_label, 0, -10);
	lv_obj_align(selected_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_set_style_radius(selected_label, 0, 0);
	// accent
	accent_label = lv_label_create(selected);
	lv_obj_set_style_text_font(accent_label, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(accent_label, lv_color_hex(0xF58E27), 0);
	lv_obj_set_flex_grow(accent_label, 1);
	lv_obj_set_pos(accent_label, 0, -10);
	lv_obj_align(accent_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_set_style_radius(accent_label, 0, 0);
	
	list_items[0] = selected;

	// middle container
	lv_obj_t *middle = lv_obj_create(root);
	lv_obj_set_width(middle, LV_PCT(100));
	lv_obj_set_flex_grow(middle, 1);
	lv_obj_set_flex_flow(middle, LV_FLEX_FLOW_ROW);

    // left word list
	list = lv_obj_create(middle);
	lv_obj_set_width(list, 45);
	lv_obj_set_height(list, LV_PCT(100));
	lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
	for (int i = 1; i < list_element_count; i++)
	{
		lv_obj_t *item = lv_obj_create(list);
		lv_obj_set_size(item, 45, 32);

		lv_obj_t *label = lv_label_create(item);
		lv_obj_set_width(label, LV_PCT(100));
		lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
		lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, 0);
		lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
		lv_obj_set_pos(label, 0, -10);

		list_items[i] = item;

		lv_obj_set_style_pad_all(item, 0, 0);
		lv_obj_set_style_pad_row(item, 0, 0);
		lv_obj_set_style_pad_column(item, 0, 0);
		lv_obj_remove_flag(item, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_radius(item, 0, 0);
		lv_obj_set_style_pad_all(label, 0, 0);
		lv_obj_set_style_pad_row(label, 0, 0);
		lv_obj_set_style_pad_column(label, 0, 0);
		lv_obj_remove_flag(label, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_radius(label, 0, 0);
		lv_obj_set_style_border_width(label, 0, 0);
	}
	

    // right details panel
	lv_obj_t *details = lv_obj_create(middle);
	lv_obj_set_flex_grow(details, 1);
	lv_obj_set_height(details, LV_PCT(100));
	lv_obj_set_flex_align(details, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	// details label
	details_label = lv_label_create(details);
	lv_obj_set_style_text_font(details_label, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(details_label, lv_color_hex(0xF58E27), 0);
	lv_obj_set_width(details_label, LV_PCT(100));
	lv_label_set_long_mode(details_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(details_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_set_style_radius(details_label, 0, 0);



    // bottom options row
	lv_obj_t *bottom = lv_obj_create(root);
	//AAAAAAAAAAAA
	lv_obj_set_width(bottom, LV_PCT(100));
	lv_obj_set_height(bottom, 30);
	lv_obj_set_flex_flow(bottom, LV_FLEX_FLOW_ROW);
	for (int i = 0; i < BOTTOM_ITEM_COUNT; i++)
	{
		lv_obj_t *item = lv_obj_create(bottom);
		lv_obj_set_height(item, LV_PCT(100));
		lv_obj_set_width(item, LV_SIZE_CONTENT);
		lv_obj_set_flex_grow(item, 1);

		lv_obj_t *label = lv_label_create(item);
		lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
		lv_obj_set_width(label, LV_SIZE_CONTENT);
		lv_obj_center(label);

		bottom_items[i] = item;
		bottom_labels[i] = label;

		lv_obj_set_style_pad_all(item, 0, 0);
		lv_obj_set_style_pad_row(item, 0, 0);
		lv_obj_set_style_pad_column(item, 0, 0);
		lv_obj_remove_flag(item, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_radius(item, 0, 0);
		lv_obj_set_style_pad_all(label, 0, 0);
		lv_obj_set_style_pad_row(label, 0, 0);
		lv_obj_set_style_pad_column(label, 0, 0);
		lv_obj_remove_flag(label, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_radius(label, 0, 0);
		lv_obj_set_style_border_width(label, 0, 0);
	}
	lv_label_set_text(bottom_labels[1], "search");
	lv_label_set_text(bottom_labels[2], "EN -> JP");
	lv_label_set_text(bottom_labels[3], "options");




	populate_list(0);
	update_bottom_highlight();
	update_results();
	

	g = lv_group_create();
	lv_indev_set_group(kb_indev, g);
	lv_group_add_obj(g, list);
	lv_group_focus_obj(list);
	lv_obj_add_event_cb(list, keyboard_event_cb, LV_EVENT_ALL, NULL);


	

	///////////////////
	// styling shotgun
	///////////////////
	// root
	lv_obj_set_style_pad_all(root, 0, 0);
	lv_obj_set_style_pad_row(root, 0, 0);
	lv_obj_set_style_pad_column(root, 0, 0);
	lv_obj_remove_flag(root, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(root, 0, 0);
	// search
	lv_obj_set_style_pad_all(search, 0, 0);
	lv_obj_set_style_pad_row(search, 0, 0);
	lv_obj_set_style_pad_column(search, 0, 0);
	lv_obj_remove_flag(search, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(search, 0, 0);
	// selected word
	lv_obj_set_style_pad_all(selected, 0, 0);
	lv_obj_set_style_pad_row(selected, 0, 0);
	lv_obj_set_style_pad_column(selected, 0, 0);
	lv_obj_remove_flag(selected, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(selected, 0, 0);
	// middle
	lv_obj_set_style_pad_all(middle, 0, 0);
	lv_obj_set_style_pad_row(middle, 0, 0);
	lv_obj_set_style_pad_column(middle, 0, 0);
	lv_obj_remove_flag(middle, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(middle, 0, 0);
	lv_obj_set_style_border_width(middle, 0, 0);
	// word list
	lv_obj_set_style_pad_all(list, 0, 0);
	lv_obj_set_style_pad_row(list, 0, 0);
	lv_obj_set_style_pad_column(list, 0, 0);
	lv_obj_remove_flag(list, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(list, 0, 0);
	lv_obj_set_style_border_width(list, 0, 0);
	// details
	lv_obj_set_style_pad_all(details, 0, 0);
	lv_obj_set_style_pad_row(details, 0, 0);
	lv_obj_set_style_pad_column(details, 0, 0);
	lv_obj_remove_flag(details, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(details, 0, 0);
	// bottom
	lv_obj_set_style_pad_all(bottom, 0, 0);
	lv_obj_set_style_pad_row(bottom, 0, 0);
	lv_obj_set_style_pad_column(bottom, 0, 0);
	lv_obj_remove_flag(bottom, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(bottom, 0, 0);
	lv_obj_set_style_border_width(bottom, 0, 0);

	



}



