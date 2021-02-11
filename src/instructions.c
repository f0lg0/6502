#include <stdio.h>
#include "include/instructions.h"

static uint8_t IMM(void) {
    printf("(MODE) Running in IMM mode.\n");
    return 0;
}

static uint8_t LDA(void) {
    printf("(LDA) Called LDA.\n");
    return 0;
}

struct instruction lookup[256] = {
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 },
        { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }, { "LDA", &LDA, &IMM, 2 }
};

void inst_exec(uint8_t opcode, uint32_t* cycles) {
//    *(cycles) = lookup[opcode].cycles;

    (*(lookup[opcode].mode))();
    (*(lookup[opcode].op))();

    *(cycles) -= 1;
}
