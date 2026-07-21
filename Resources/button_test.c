#include <nuttx/config.h>
#include <stdio.h>
#include <unistd.h>
#include <arch/board/board.h>
#include <nuttx/arch.h>

#define BUTTON1 PIN_UART2_TXD
#define BUTTON2 PIN_UART2_RXD

int main(int argc, char *argv[]) {


    board_gpio_config(BUTTON1, 0, true, true, PIN_PULLUP);
    board_gpio_config(BUTTON2, 0, true, true, PIN_PULLUP);

    bool last_b1 = true;
    bool last_b2 = true;

    while (1) {
        bool b1 = board_gpio_read(BUTTON1);
        bool b2 = board_gpio_read(BUTTON2);

        if (b1 != last_b1 || b2 != last_b2) {
            printf("D02: %s | D03: %s\n",
                   b1 == false ? "PRESSED" : "RELEASED",
                   b2 == false ? "PRESSED" : "RELEASED");
            fflush(stdout);

            last_b1 = b1;
            last_b2 = b2;
        }
    }
    return 0;
}
