#include "interface.h"

#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>

#include "../cpu/cpu.h"
#include "../mem/mem.h"

void interface_display_header(void) {
    mvprintw(1, 3, "6502 Emulator");
    mvprintw(2, 3, "-----------------------");
    mvprintw(3, 5, "Commands:");
    mvprintw(4, 7, "Enter: executes next instruction");
    mvprintw(5, 7, "r: Resets CPU");
    mvprintw(6, 7, "q: Quits");
    mvprintw(7, 3, "-----------------------");
}

/**
 * interface_display_cpu: prints CPU status to the screen using ncurses
 * @param void
 * @return void
 * */
void interface_display_cpu(void) {
    mvprintw(10, 3, "ac: 0x%X pc: 0x%X sp: 0x%X x: 0x%X y: 0x%X sr: 0x%X",
             cpu.ac, cpu.pc, cpu.sp, cpu.x, cpu.y, cpu.sr);
}

void interface_display_mem(void) {
    struct mem* mp = mem_get_ptr();
    mvprintw(12, 3, "Zero Page:");

    uint8_t x = 3;
    uint8_t y = 14;
    for (uint16_t i = 0; i < 256; i++) {
        mvprintw(y, x, "%02X ", mp->zero_page[i]);
        if (x % WIN_ROWS == 0) {
            y += 1;
            x = 3;
        } else {
            x += 3;
        }
    }

    y += 2;
    mvprintw(y, 3, "Stack:");
    y += 2;
    x = 3;

    for (uint16_t i = 0; i < 256; i++) {
        mvprintw(y, x, "%02X ", mp->stack[i]);
        if (x % WIN_ROWS == 0) {
            y += 1;
            x = 3;
        } else {
            x += 3;
        }
    }

    y += 2;
    mvprintw(y, 3, "Program Data:");
    y += 2;
    x = 3;

    for (uint16_t i = 0x8000 - 0x0200; i < 0x8000 - 0x0200 + 256; i++) {
        mvprintw(y, x, "%02X ", mp->data[i]);
        if (x % WIN_ROWS == 0) {
            y += 1;
            x = 3;
        } else {
            x += 3;
        }
    }

    mvprintw(y + 2, 3, "[...]");
}