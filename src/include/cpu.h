#ifndef INC_6502_CPU_H
#define INC_6502_CPU_H

#include <stdint.h>

#include "mem.h"

struct central_processing_unit {
    uint16_t pc;
    uint8_t sp;
    uint8_t ac;
    uint8_t x;
    uint8_t y;

    /*
     * Status Register:
     *
     * bit 0: Carry
     * bit 1: Zero
     * bit 2: Interrupt
     * bit 3: Decimal
     * bit 4: Break
     * bit 5: 0
     * bit 6: Overflow (V)
     * bit 7: Negative
     * */
    uint8_t sr;
};

extern struct central_processing_unit cpu;

void cpu_reset(void);
uint8_t cpu_extract_sr(uint8_t flag);
uint8_t cpu_mod_sr(uint8_t flag, uint8_t val);
uint8_t cpu_fetch();
void cpu_exec();
void cpu_init(void);

#endif
