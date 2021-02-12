#include <stdio.h>
#include "include/instructions.h"

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
    printf("(inst_exec) cycles: %d\n", *(cycles));
    printf("(debug) op: %s\n", lookup[opcode].name);

    if (*(cycles) == 0) {
        *(cycles) = lookup[opcode].cycles;
        printf("(inst_exec) cycles: %d\n", *(cycles));

        (*(lookup[opcode].mode))();
        (*(lookup[opcode].op))();
    }

    *(cycles) -= 1;
    printf("(inst_exec) cycles: %d\n", *(cycles));
}
