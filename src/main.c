#include <stdio.h>
#include <stdint.h>

#include "include/mem.h"
#include "include/cpu.h"
#include "include/interface.h"

int main(int argc, char** argv) {
    uint8_t keypad[2] = {0};

    printf("(main): %d, %p\n", argc, (void*)argv);

    mem_init();
    cpu_init();
    cpu_reset();

    inter_init_display();

    while (1) {
        inter_event_handler(keypad);

        if (inter_should_quit()) {
            break;
        }

        if (keypad[0]) {
            cpu_exec();
        }
        keypad[0] = 0;
    }


    mem_dump();
    return 0;
}
