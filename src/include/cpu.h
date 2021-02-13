#ifndef INC_6502_CPU_H
#define INC_6502_CPU_H

#include <stdint.h>

#include "mem.h"

// note that they are signed
struct regs {
    int16_t pc;
    int8_t sp;
    int8_t ac;
    int8_t x;
    int8_t y;

    // for the sr we use the dedicated macros in cpu_set_reg()
};

void cpu_reset(void);
void cpu_set_reg(struct regs regs);
uint8_t cpu_extract_sr(uint8_t flag);
uint8_t cpu_mod_sr(uint8_t flag, uint8_t val);
uint8_t cpu_fetch();
void cpu_exec();
void cpu_init();

#endif
