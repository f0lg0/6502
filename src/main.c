#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"
#include "mem/mem.h"
#include "peripherals/interface.h"
#include "peripherals/kinput.h"

uint8_t DEBUG = 0;

int main(void) {
    mem_init();
    cpu_init();
    cpu_reset();

    WINDOW* win = newwin(WIN_ROWS, WIN_COLS, 0, 0);
    if ((win = initscr()) == NULL) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }

    curs_set(0);
    noecho();
    box(win, 0, 0);
    wrefresh(win);

    interface_display_header();
    wrefresh(win);

    do {
        interface_display_cpu();
        interface_display_mem();
        wrefresh(win);

        kinput_listen();
    } while (!kinput_should_quit());

    delwin(win);
    endwin();

    mem_dump();
    return 0;
}
