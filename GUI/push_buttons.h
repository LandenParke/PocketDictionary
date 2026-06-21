#ifndef PUSH_BUTTONS_H
#define PUSH_BUTTONS_H

#include <stdbool.h>
#include <arch/board/board.h>
#include <nuttx/arch.h>

#define BTN_PIN_UP    PIN_D02
#define BTN_PIN_DOWN  PIN_D03
#define BTN_PIN_LEFT  PIN_D04
#define BTN_PIN_RIGHT PIN_D05
#define BTN_PIN_OK    PIN_D06

//Initialize the buttons
static inline void spresense_buttons_init(void)
{
    board_gpio_config(BTN_PIN_UP,    0, true, true, PIN_PULLUP);
    board_gpio_config(BTN_PIN_DOWN,  0, true, true, PIN_PULLUP);
    board_gpio_config(BTN_PIN_LEFT,  0, true, true, PIN_PULLUP);
    board_gpio_config(BTN_PIN_RIGHT, 0, true, true, PIN_PULLUP);
    board_gpio_config(BTN_PIN_OK,    0, true, true, PIN_PULLUP);
}

//For polling each button
static inline bool btn_up_pressed(void)    { return board_gpio_read(BTN_PIN_UP)    == false; }
static inline bool btn_down_pressed(void)  { return board_gpio_read(BTN_PIN_DOWN)  == false; }
static inline bool btn_left_pressed(void)  { return board_gpio_read(BTN_PIN_LEFT)  == false; }
static inline bool btn_right_pressed(void) { return board_gpio_read(BTN_PIN_RIGHT) == false; }
static inline bool btn_ok_pressed(void)    { return board_gpio_read(BTN_PIN_OK)    == false; }


static void poll_buttons(void);


#endif
