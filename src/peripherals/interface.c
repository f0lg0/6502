#include "interface.h"

#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>

#include "../cpu/cpu.h"

void interface_display_cpu(void) {
    mvprintw(2, 0, "ac: 0x%X pc: 0x%X sp: 0x%X x: 0x%X y: 0x%X sr: 0x%X",
             cpu.ac, cpu.pc, cpu.sp, cpu.x, cpu.y, cpu.sr);
}