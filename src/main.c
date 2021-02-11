#include <stdio.h>

#include "include/mem.h"
#include "include/cpu.h"

int main(int argc, char** argv) {
    printf("(main): %d, %p\n", argc, (void*)argv);

    mem_init();
    mem_dump();
    
    struct mem* mp = mem_get_ptr();

    cpu_reset();
    cpu_exec(2, mp);

    return 0;
}
