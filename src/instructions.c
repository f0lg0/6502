#include <stdio.h>

#include "include/instructions.h"
#include "include/cpu.h"

/*
 * =============================================
 * MODES
 * =============================================
 */

/**
 * IMM: Immediate Mode
 * @param void
 * @return 0
 */
static uint8_t IMM(void) {
    printf("(MODE) Running in IMM mode.\n");
    return 0;
}

/*
 * =============================================
 * OPERATIONS
 * =============================================
 */

/**
 * XXX: Used to handle unknown opcodes
 * @param void
 * @return 0
 */
static uint8_t XXX(void)  {
    printf("(UNKNOWN) opcode not recognized.\n");
    return 0;
}

/**
 * LDA: Load Accumulator
 * @param void
 * @return 0
 */
static uint8_t LDA(void) {
    printf("(LDA) Called LDA.\n");

    uint8_t val = cpu_fetch();

    struct regs rs;

    rs.ac = val;
    rs.x = -1;
    rs.y = -1;
    rs.sp = -1;
    rs.pc = -1;

    cpu_set_regs(rs);

    return 0;
}

// the populated matrix of opcodes, not a clean solution but it's easily understandable
struct instruction lookup[256] = {
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 },
        { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }, { "XXX", &XXX, &IMM, 2 }
};

/**
 * inst_exec: Parse and execute a fetched instruction
 * @param opcode The retrieved opcode from cpu_exec()
 * @param cycles The amount of clock cycles happening
 * @return void
 */
void inst_exec(uint8_t opcode, uint32_t* cycles) {
    *(cycles) = lookup[opcode].cycles;

    (*(lookup[opcode].mode))();
    (*(lookup[opcode].op))();

    printf("(inst_exec) cycles: %d, %p\n", *(cycles), (void *)cycles);
}
