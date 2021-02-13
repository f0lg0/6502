#ifndef INC_6502_MEM_H
#define INC_6502_MEM_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_MEM 1024 * 64

struct mem {
    uint8_t zero_page[0x100];
    uint8_t stack[0x100];
    uint8_t last_six[0x06];
    uint8_t data[MAX_MEM - 0x206];
};

size_t mem_size(void);
void mem_init(void);
int mem_dump(void);
struct mem* mem_get_ptr(void);

#endif
