#include "kinput.h"

#include <ncurses.h>
#include <stdint.h>

#include "../cpu/cpu.h"
#include "interface.h"

uint8_t QUIT = 0;
void kin_tui_listen(void) {
    char c = getch();
    if (c == '\n') {
        cpu_exec();
    } else if (c == 'r') {
        cpu_reset();
    } else if (c == 'q') {
        QUIT = 1;
    }
}

uint8_t kin_tui_should_quit(void) { return QUIT; }
