#include <stdio.h>

#include "include/instructions.h"
#include "include/cpu.h"

/*
 * =============================================
 * MODES
 * =============================================
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

static uint8_t XXX(void)  {
    printf("(UNKNOWN) opcode not recognized.\n");
    return 0;
}

static uint8_t LDA(void) {
    printf("(LDA) Called LDA.\n");

    uint8_t val = cpu_fetch();

    struct regs rs;

    rs.ac = val;
    rs.x = -1;
    rs.y = -1;
    rs.sp = -1;
    rs.pc = -1;

    cpu_set_reg(rs);

    return 0;
}

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

void inst_exec(uint8_t opcode, uint32_t* cycles) {
    printf("(inst_exec) cycles: %d, %p\n", *(cycles), (void*)cycles);

    // running instruction at a single time
    if (*(cycles) == 0) {
        *(cycles) = lookup[opcode].cycles;
        printf("(inst_exec if_stat) cycles: %d\n", *(cycles));

        (*(lookup[opcode].mode))();
        (*(lookup[opcode].op))();
        printf("EXECUTED\n");
    }

    *(cycles) -= 1;
    printf("(inst_exec end) cycles: %d, %p\n", *(cycles), (void *)cycles);
}
