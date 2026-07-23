


#include <stdio.h>
#include <nuttx/config.h>
#include <unistd.h>
#include <sys/boardctl.h>
#include <lvgl/lvgl.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <lvgl/demos/lv_demos.h>



#include <sys/mount.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sqlite3.h>
#include <jp_fonts.h>
#include <romaji.h>
#include <dict.h>
static void create_ui();
static void populate_list(int start);
static void update_bottom_highlight();
static void update_results();
static void update_search_bar(char *f_word, char *s_word);

// lookup results
// fill more elements + format later
typedef struct {
    const char *word;
	const char *accent;
    const char *detail;
} dict_entry;
// word + details

static const dict_result *entries; // dict.h entry struct





/////////////////////////////////////////
// INPUT
/////////////////////////////////////////

static lv_indev_t *kb_indev;


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



#define BOTTOM_ITEM_COUNT 4
static int bottom_sel_index = 0;
static int window_start = 0;
static int results_count = 0;
static char search_word[512] = "";
static char furigana_word[512] = "";
static lv_obj_t *selected_label;
static lv_obj_t *accent_label;
static lv_obj_t *details_label;
static lv_obj_t *furigana;
static lv_obj_t *search;


static void poll_keyboard(void)
{
	char c = '0';
	read(STDIN_FILENO, &c, 1);

	if (c > '0') {
		printf("keycode read: %d\n", (unsigned char)c);
	}
	
	// any qwerty input
	if (c >= 'a' && c <= 'z') {
		int len = strlen(search_word);
		search_word[len] = c;
		search_word[len + 1] = '\0';
		romaji_to_kana(search_word, furigana_word, sizeof(furigana_word));
		printf("f_word: %s\ns_word: %s\n", furigana_word, search_word);
		lv_obj_set_style_text_color(search, lv_color_hex(0xF58E27), 0);
		lv_obj_set_style_text_color(furigana, lv_color_hex(0xF58E27), 0);
		update_search_bar(furigana_word, search_word);
	}
	// backspace
	if (c == 127) {
		int len = strlen(search_word);
		search_word[len - 1] = '\0';
		romaji_to_kana(search_word, furigana_word, sizeof(furigana_word));
		printf("f_word: %s\ns_word: %s\n", furigana_word, search_word);
		update_search_bar(furigana_word, search_word);
	}
	if (c == '1') {
		if (window_start > 0) {
			populate_list(window_start - 1);
		}
	}
	if (c == '2') {
		if (window_start < results_count - 1) {
			populate_list(window_start + 1);
		}
	}
	if (c == '3') {
		if (bottom_sel_index > 0) {
			bottom_sel_index--;
			update_bottom_highlight();
		}
	}
	if (c == '4') {
		if (bottom_sel_index < BOTTOM_ITEM_COUNT - 1) {
			bottom_sel_index++;
			update_bottom_highlight();
		}
	}
	// enter key
	if (c == '\r' || c == '\n') {
		results_count = dict_search(furigana_word, &entries);
		search_word[0] = '\0';
		lv_obj_set_style_text_color(search, lv_color_hex(0xffffff), 0);
		update_search_bar(furigana_word, search_word);
		printf("search cleared");
		lv_label_set_text(search, "type to search");
		furigana_word[0] = '\0';
		populate_list(0);
	}
}


static void keypad_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
	poll_keyboard();
}




static void mount_hostfs(void)
{
    mkdir("/host", 0777);
	// hardcoded, dict.db at /usr/nuttx_stuff
    int ret = mount(NULL, "/host", "hostfs", 0, "fs=/usr/nuttx_stuff");

    if (ret < 0) {
        perror("hostfs mount failed\n");
    } else {
        printf("hostfs mounted\n");
    }
}



/////////////////////////////////////////
// MAIN
/////////////////////////////////////////

int main(int argc, FAR char *argv[])
{
	lv_nuttx_dsc_t info;
	lv_nuttx_result_t result;
	
	lv_init();

	lv_nuttx_dsc_init(&info);
	info.fb_path = "/dev/lcd0";

	lv_nuttx_init(&info, &result);

	if (result.disp == NULL) {
		LV_LOG_ERROR("lv_demos initialization failure!");
		return 1;
	}

	// db
	mount_hostfs();
	dict_open("/host/dict.db");
	dict_search("ame", &entries);



	// input
	enable_raw_mode();
	set_stdin_nonblock();
	printf("raw input mode set\n");
	kb_indev = lv_indev_create();
	lv_indev_set_type(kb_indev, LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_read_cb(kb_indev, keypad_read_cb);
	printf("lvgl indev created\n");
	

	create_ui();
	
	
  	while (1) {
	uint32_t idle;
	idle = lv_timer_handler();
	// minimum sleep of 1ms
	idle = idle ? idle : 1;
	usleep(idle * 1000);
	}
}













/////////////////////////////////////////
// LAYOUT
/////////////////////////////////////////
 
// screen size
int sx = 320;
int sy = 240;
// horz/vert seperations
int h1 = 40;
int h2 = 210;
int v1 = 40;


// live update search bar
static void update_search_bar(char *f_word, char *s_word) {
	lv_label_set_text(furigana, f_word);
	lv_label_set_text(search, s_word);
}

// word list
#define list_element_count 5
static lv_obj_t *list_items[list_element_count];

// fill middle ui elements using dict entry array
static void populate_list(int start) {
    window_start = start;
    lv_label_set_text(selected_label, entries[start].word);
	lv_label_set_text(accent_label, entries[start].accent);
    lv_label_set_text(details_label, entries[start].detail);
	printf(entries[start].word);
	printf(entries[start].detail);

    for (int i = 0; i < list_element_count; i++){
		lv_obj_t *label = lv_obj_get_child(list_items[i], 0);
        int idx = start + i;
        if (idx < results_count) {
			lv_label_set_text(label, entries[idx].word);
		} else {
			lv_label_set_text(label, "");
		}
    }
	update_results();
}

// bottom bar
static lv_obj_t *bottom_items[BOTTOM_ITEM_COUNT];
static lv_obj_t *bottom_labels[BOTTOM_ITEM_COUNT];
static lv_obj_t *bot_item;
static lv_obj_t *bot_label;

static void update_bottom_highlight() {
	printf("update_bottom does nothing lol");
}
static void update_results(void) {
	lv_label_set_text_fmt(bot_label, "%d/%d", window_start+1, results_count);
}








static void create_ui() {
	lv_obj_t *scr = lv_screen_active();
	lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

	// using 24px bitmap from noto sans CJK jp regular
	lv_obj_set_style_text_font(scr, &jp_font_24, 0);

	// root
	lv_obj_t *root = lv_obj_create(scr);
	lv_obj_set_size(root, LV_PCT(100), LV_PCT(100));
	lv_obj_set_flex_flow(root, LV_FLEX_FLOW_COLUMN);
	
	// top container
	lv_obj_t *top = lv_obj_create(root);
	lv_obj_set_width(top, LV_PCT(100));
	lv_obj_set_height(top, 40);
	// top search furigana
	furigana = lv_label_create(top);
	lv_label_set_text(furigana, "");
	lv_obj_set_style_text_font(furigana, &jp_font_16_hiragana, 0);
	lv_obj_set_height(furigana, 16);
	// top search 
	search = lv_label_create(top);
	lv_label_set_text(search, "type to search");
	lv_obj_set_style_text_font(search, &lv_font_montserrat_14, 0);
	lv_obj_set_height(search, 14);
	lv_obj_set_pos(search, 0, 16);
	


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
	lv_obj_set_style_text_font(accent_label, &lv_font_montserrat_10, 0);
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
	static lv_obj_t *list;
	list = lv_obj_create(middle);
	lv_obj_set_width(list, 40);
	lv_obj_set_height(list, LV_PCT(100));
	lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
	for (int i = 1; i < list_element_count; i++)
	{
		lv_obj_t *item = lv_obj_create(list);
		lv_obj_set_size(item, 40, 32);
		lv_obj_set_style_bg_opa(item, LV_OPA_TRANSP, 0);

		lv_obj_t *label = lv_label_create(item);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
		lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, 0);
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
	lv_obj_set_style_text_font(details_label, &lv_font_montserrat_10, 0);
	lv_obj_set_style_text_color(details_label, lv_color_hex(0xF58E27), 0);
	lv_obj_set_width(details_label, LV_PCT(100));
	lv_label_set_long_mode(details_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(details_label, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_set_style_radius(details_label, 0, 0);



	// bottom options row
	lv_obj_t *bottom = lv_obj_create(list);
	//AAAAAAAAAAAA
	lv_obj_set_style_bg_opa(bottom, LV_OPA_TRANSP, 0);
	lv_obj_set_width(bottom, LV_PCT(100));
	lv_obj_set_height(bottom, 20);
	lv_obj_set_flex_flow(bottom, LV_FLEX_FLOW_ROW);
	
	bot_item = lv_obj_create(bottom);
	lv_obj_set_height(bottom, 40);
	lv_obj_set_style_bg_opa(bot_item, LV_OPA_TRANSP, 0);
	lv_obj_set_height(bot_item, LV_PCT(100));
	lv_obj_set_width(bot_item, LV_SIZE_CONTENT);
	lv_obj_set_flex_grow(bot_item, 1);

	bot_label = lv_label_create(bot_item);
	lv_obj_set_style_bg_opa(bot_label, LV_OPA_TRANSP, 0);
	lv_obj_set_style_text_color(bot_label, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_text_font(bot_label, &lv_font_montserrat_10, 0);
	lv_obj_set_width(bot_label, LV_SIZE_CONTENT);
	lv_obj_center(bot_label);

	lv_obj_set_style_pad_all(bot_item, 0, 0);
	lv_obj_set_style_pad_row(bot_item, 0, 0);
	lv_obj_set_style_pad_column(bot_item, 0, 0);
	lv_obj_remove_flag(bot_item, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(bot_item, 0, 0);
	lv_obj_set_style_pad_all(bot_label, 0, 0);
	lv_obj_set_style_pad_row(bot_label, 0, 0);
	lv_obj_set_style_pad_column(bot_label, 0, 0);
	lv_obj_remove_flag(bot_label, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(bot_label, 0, 0);
	lv_obj_set_style_border_width(bot_label, 0, 0);
	



	populate_list(0);
	update_bottom_highlight();


	

	///////////////////
	// styling shotgun
	///////////////////
	// root
	lv_obj_set_style_bg_color(root, lv_color_hex(0x202020), 0);
	lv_obj_set_style_pad_all(root, 0, 0);
	lv_obj_set_style_pad_row(root, 0, 0);
	lv_obj_set_style_pad_column(root, 0, 0);
	lv_obj_remove_flag(root, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(root, 0, 0);
	// top
	lv_obj_set_style_bg_opa(top, LV_OPA_TRANSP, 0);
	lv_obj_set_style_pad_all(top, 0, 0);
	lv_obj_set_style_pad_row(top, 0, 0);
	lv_obj_set_style_pad_column(top, 0, 0);
	lv_obj_remove_flag(top, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(top, 0, 0);
	// furigana
	lv_obj_set_style_text_color(furigana, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_pad_all(furigana, 0, 0);
	lv_obj_set_style_pad_row(furigana, 0, 0);
	lv_obj_set_style_pad_column(furigana, 0, 0);
	lv_obj_remove_flag(furigana, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(furigana, 0, 0);
	// search
	lv_obj_set_style_text_color(search, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_pad_all(search, 0, 0);
	lv_obj_set_style_pad_row(search, 0, 0);
	lv_obj_set_style_pad_column(search, 0, 0);
	lv_obj_remove_flag(search, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(search, 0, 0);
	// selected word
	lv_obj_set_style_text_color(selected, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_bg_opa(selected, LV_OPA_TRANSP, 0);
	lv_obj_set_style_pad_all(selected, 0, 0);
	lv_obj_set_style_pad_row(selected, 0, 0);
	lv_obj_set_style_pad_column(selected, 0, 0);
	lv_obj_remove_flag(selected, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(selected, 0, 0);
	// middle
	lv_obj_set_style_bg_opa(middle, LV_OPA_TRANSP, 0);
	lv_obj_set_style_pad_all(middle, 0, 0);
	lv_obj_set_style_pad_row(middle, 0, 0);
	lv_obj_set_style_pad_column(middle, 0, 0);
	lv_obj_remove_flag(middle, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(middle, 0, 0);
	lv_obj_set_style_border_width(middle, 0, 0);
	// word list
	lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, 0);
	lv_obj_set_style_pad_all(list, 0, 0);
	lv_obj_set_style_pad_row(list, 0, 0);
	lv_obj_set_style_pad_column(list, 0, 0);
	lv_obj_remove_flag(list, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(list, 0, 0);
	lv_obj_set_style_border_width(list, 0, 0);
	// details
	lv_obj_set_style_text_color(details, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_bg_opa(details, LV_OPA_TRANSP, 0);
	lv_obj_set_style_pad_all(details, 0, 0);
	lv_obj_set_style_pad_row(details, 0, 0);
	lv_obj_set_style_pad_column(details, 0, 0);
	lv_obj_remove_flag(details, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(details, 0, 0);
	// bottom
	lv_obj_set_style_bg_opa(bottom, LV_OPA_TRANSP, 0);
	lv_obj_set_style_pad_all(bottom, 0, 0);
	lv_obj_set_style_pad_row(bottom, 0, 0);
	lv_obj_set_style_pad_column(bottom, 0, 0);
	lv_obj_remove_flag(bottom, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_radius(bottom, 0, 0);
	lv_obj_set_style_border_width(bottom, 0, 0);

	



}


