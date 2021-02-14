#include <stdio.h>

#include "mem/mem.h"
#include "cpu/cpu.h"
#include "peripherals/interface.h"
#include "peripherals/kinput.h"

uint8_t DEBUG;

int main(int argc, char** argv) {
    printf("(main): %d, %p\n", argc, (void*)argv);

    mem_init();
    cpu_init();
    cpu_reset();

    inter_init_display();

    while (1) {
        kin_start();

        if (inter_should_quit()) {
            break;
        }
    }


    mem_dump();
    inter_stop_display();
    return 0;
}
