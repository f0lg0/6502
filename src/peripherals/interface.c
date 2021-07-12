/*
 * NOTE: this module is trash. I am not a game/graphics developer, this
 * is my first time creating a GUI for a program (I only have experience in
 * web-dev). I am interested in feedback regarding graphics performance, I know
 * there are some cool techniques but I want to focus more on the 6502 itself.
 */

#include "interface.h"

#include <SDL2/SDL_ttf.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>

#include "../cpu/cpu.h"

void inter_tui_display_cpu(void) {
    mvprintw(2, 0, "ac: 0x%X pc: 0x%X sp: 0x%X x: 0x%X y: 0x%X sr: 0x%X",
             cpu.ac, cpu.pc, cpu.sp, cpu.x, cpu.y, cpu.sr);
}