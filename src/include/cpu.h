#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "mem.h"

void cpu_reset(void);
uint8_t cpu_extract_sr(uint8_t flag);
uint8_t cpu_mod_sr(uint8_t flag, uint8_t val);
uint8_t cpu_fetch(uint32_t* cycles, struct mem* mem);
void cpu_exec(uint32_t cycles, struct mem* mem_ptr);

#endif
