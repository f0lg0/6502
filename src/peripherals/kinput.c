#include "kinput.h"

#include <ncurses.h>
#include <stdint.h>

#include "../cpu/cpu.h"
#include "interface.h"

uint8_t QUIT = 0;

/**
 * kinput_listen: listens for keyboard events and exuctes respective actions
 * @param void
 * @return void
 * */
void kinput_listen(void) {
    char c = getch();

    switch (c) {
        case '\n':
            cpu_exec();
            break;

        case 'r':
            cpu_reset();
            break;

        case 'q':
            QUIT = 1;
            break;

        default:
            break;
    }
}

// kinput_should_quit: sends quit signal by returning QUIT status
uint8_t kinput_should_quit(void) { return QUIT; }
