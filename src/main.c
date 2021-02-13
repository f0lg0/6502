#include <stdio.h>
#include <stdint.h>

#include "include/mem.h"
#include "include/cpu.h"
#include "include/interface.h"
#include "include/kinput.h"

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
