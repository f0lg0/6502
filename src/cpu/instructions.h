#ifndef INC_6502_INSTRUCTIONS_H
#define INC_6502_INSTRUCTIONS_H

#include <stdint.h>

extern uint8_t DEBUG;

struct instruction {
    char* name;
    uint8_t (*op)(void);
    uint8_t (*mode)(void);
    uint8_t cycles;
};

void inst_exec(uint8_t opcode, uint32_t* cycles);
void reset(void);

#endif
