#include <ncurses.h>
#include <stdio.h>

#include "cpu/cpu.h"
#include "mem/mem.h"
#include "peripherals/interface.h"
#include "peripherals/kinput.h"

uint8_t DEBUG = 0;

int main(void) {
    mem_init();
    cpu_init();
    cpu_reset();

    initscr();
    curs_set(0);
    noecho();
    addstr("6502 Emulator\n-----------------\n");
    refresh();

    while (1) {
        inter_tui_display_cpu();
        refresh();
        kin_tui_listen();

        if (kin_tui_should_quit()) {
            break;
        }
    }

    endwin();

    mem_dump();
    return 0;
}
