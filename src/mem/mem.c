#include "mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../utils/misc.h"

/**
 * The memory:
 *
 *  - RESERVED: 256 bytes 0x0000 to 0x00FF -> Zero Page
 *  - RESERVED: 256 bytes 0x0100 to 0x01FF -> System Stack
 *  - PROGRAM DATA: 0x10000 - 0x206
 *  - RESERVED: last 6 bytes of memory
 *
 *  pages are split into different arrays
 *
 * */
struct mem memory;

/**
 * load_program: Loads binary into program data memory
 * @param path Path to binary on hosst machine
 * @return void
 * */
static void load_program(char* path) {
    FILE* fp = fopen(path, "rb");

    if (fp == NULL) {
        fprintf(stderr, "[FAILED] Error while loading provided file.\n");
        exit(1);
    }

    struct stat st;
    stat(path, &st);
    size_t fsize = st.st_size;

    size_t bytes_read =
        fread(memory.data + (0x8000 - 0x0200), 1, sizeof(memory.data), fp);

    if (bytes_read != fsize) {
        fprintf(
            stderr,
            "[FAILED] Amount of bytes read doesn't match read file size.\n");
        exit(1);
    }

    fclose(fp);
}

/**
 * mem_init: Initialize the memory to its initial state
 *
 * @param void
 * @return void
 * */
void mem_init(char* filename) {
    memset(memory.zero_page, 0, sizeof(memory.zero_page));
    memset(memory.stack, 0, sizeof(memory.stack));
    memset(memory.data, 0, sizeof(memory.data));

    // im not really sure about this
    memory.last_six[0] = 0xA;
    memory.last_six[1] = 0xB;
    memory.last_six[2] = 0xC;
    memory.last_six[3] = 0xD;
    memory.last_six[4] = 0xE;
    memory.last_six[5] = 0xF;

    if (filename == NULL) {
        fprintf(stderr, "[FAILED] No binary program was provided.\n");
        exit(1);
    } else {
        load_program(filename);
    }
}

/**
 * mem_get_ptr: returns pointer to currently active memory struct
 * */
struct mem* mem_get_ptr(void) {
    struct mem* mp = &memory;
    return mp;
}

/**
 * mem_dump: Dumps the memory to a file called dump.bin
 *
 * @param void
 * @return 0 if success, 1 if fail
 * */
int mem_dump(void) {
    // 100% there's a better way to do this

    FILE* fp = fopen("dump.bin", "wb+");
    if (fp == NULL) return 1;

    size_t wb = fwrite(memory.zero_page, 1, sizeof(memory.zero_page), fp);
    if (wb != sizeof(memory.zero_page)) {
        printf("[FAILED] Errors while dumping the zero page.\n");
        fclose(fp);
        return 1;
    }
    wb = fwrite(memory.stack, 1, sizeof(memory.stack), fp);

    if (wb != sizeof(memory.stack)) {
        printf("[FAILED] Errors while dumping the system stack.\n");
        fclose(fp);
        return 1;
    }

    wb = fwrite(memory.data, 1, sizeof(memory.data), fp);

    if (wb != sizeof(memory.data)) {
        printf("[FAILED] Errors while dumping the program data.\n");
        fclose(fp);
        return 1;
    }

    wb = fwrite(memory.last_six, 1, sizeof(memory.last_six), fp);

    if (wb != sizeof(memory.last_six)) {
        printf("[FAILED] Errors while dumping the last six reserved bytes.\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}
