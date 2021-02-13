#include "include/mem.h"
#include <string.h>

/**
 * The memory:
 *
 *  - RESERVED: 256 bytes 0x0000 to 0x00FF -> Zero Page
 *  - RESERVED: 256 bytes 0x0100 to 0x01FF -> System Stack
 *  - PROGRAM DATA: 65536 - (256*2) - 6 bytes of memory
 *  - RESERVED: last 6 bytes of memory
 *
 *  In this implementation I have split the pages, hopefully it
 *  will come in handy in the future
 *
 * */
struct mem memory;

/**
 * mem_init: Initialize the memory to its initial state
 *
 * @param void
 * @return void
 * */
void mem_init(void) {
    memset(memory.zero_page, 0, sizeof(memory.zero_page));
    memset(memory.stack, 0, sizeof(memory.stack));
    memset(memory.data, 0, sizeof(memory.data));

    // TODO: not really sure about this
    memory.last_six[0] = 0xA;
    memory.last_six[1] = 0xB;
    memory.last_six[2] = 0xC;
    memory.last_six[3] = 0xD;
    memory.last_six[4] = 0xE;
    memory.last_six[5] = 0xF;
}

struct mem* mem_get_ptr(void) {
    struct mem* mp = &memory;
    return mp;
}

/**
 * mem_dump: Dump the memory to a file called dump.bin
 *
 * @param void
 * @return 0 if success, 1 if fail
 * */
int mem_dump(void) {
    FILE* fp = fopen("dump.bin", "wb+");
    if (fp == NULL) return 1;

    size_t wb = fwrite(memory.zero_page, 1, sizeof(memory.zero_page), fp);
    if (wb != sizeof(memory.zero_page)) {
        printf("[FAILED] Errors while dumping the zero page.\n");
        return 1;
    }
    wb = fwrite(memory.stack, 1, sizeof(memory.stack), fp);

    if (wb != sizeof(memory.stack)) {
        printf("[FAILED] Errors while dumping the system stack.\n");
        return 1;
    }

    wb = fwrite(memory.data, 1, sizeof(memory.data), fp);

    if (wb != sizeof(memory.data)) {
        printf("[FAILED] Errors while dumping the program data.\n");
        return 1;
    }

    wb = fwrite(memory.last_six, 1, sizeof(memory.last_six), fp);

    if (wb != sizeof(memory.last_six)) {
        printf("[FAILED] Errors while dumping the last six reserved bytes.\n");
        return 1;
    }

    return 0;
}
