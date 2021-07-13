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
    addstr(
        "6502 Emulator\n-----------------\nCommands:\n\tEnter: executes next "
        "instruction\n\tr: Resets CPU\n\tq: Quits\n-----------------\n");
    refresh();

    while (1) {
        interface_display_cpu();
        refresh();
        kinput_listen();

        if (kinput_should_quit()) {
            break;
        }
    }

    endwin();

    mem_dump();
    return 0;
}
