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
  g_key_pressed = false;

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

#define list_element_count 4

// lookup results placeholder
static const char *all_words[] = {
    "日", "一", "国", "人", "年", "大",
    "十", "二", "本", "中", "長", "出"
};
int results_count = (sizeof(all_words)/sizeof(all_words[0]));

static lv_obj_t *list_items[list_element_count];
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
    } else if (key == LV_KEY_ENTER) {
		int idx = window_start + sel_index;

		if (idx < results_count)
		{
			printf("selected: %s\n", all_words[idx]);
			fflush(stdout);
		}
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

	if (!g)
	{
		g = lv_group_create();
		lv_group_set_default(g);
	}

	lv_group_add_obj(g, c2);
	lv_group_focus_obj(c2);

	lv_obj_add_event_cb(c2,
						keyboard_event_cb,
						LV_EVENT_KEY,
						NULL);

	if (kb_indev)
	{
		lv_indev_set_group(kb_indev, g);
	}
}



