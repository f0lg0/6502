#include <stdio.h>

#include "mem/mem.h"
#include "cpu/cpu.h"
#include "peripherals/interface.h"
#include "peripherals/kinput.h"

uint8_t DEBUG = 1;

int main(int argc, char** argv) {
    printf("(main): %d, %p\n", argc, (void*)argv);

    mem_init();
    cpu_init();
    cpu_reset();

    inter_init_display();
    inter_init_text("6502 Emulator");

    while (1) {
        kin_start();
        inter_draw();

        if (inter_should_quit()) {
            break;
        }

    }


    mem_dump();
    inter_stop_display();
    return 0;
}
