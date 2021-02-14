/*
 * NOTE: this is meant to be an extension of cpu.c, in fact these two files share
 * the same cpu struct.
 */

#include <stdio.h>
#include <stdint.h>

#include "instructions.h"
#include "cpu.h"
#include "../utils/misc.h"


// absolute address in memory
uint16_t addr_abs = 0x0000;

// relative address in memory
uint16_t addr_rel = 0x0000;

// a pointer to the fetched opcode in the cpu module
uint8_t* fetched_ptr = NULL;

/*
 * =============================================
 * MODES
 * =============================================
 *
 * [!] Return 1 if the operation needs an extra clock cycle
 */

/**
 * IMP: Implicit mode. This is used in instructions such as CLC.
 *      we target the accumulator for instructions like PHA
 * @param void
 * @return void
 */
static uint8_t IMP(void) {
    printf("(MODE) IMP.\n");

    *(fetched_ptr) = cpu.ac;
    return 0;
}

/**
 * IMM: Immediate Mode. Allow the programmer to directly specify an 8-bit constant within the instruction.
 *      LDA #10 --> load 10 into the accumulator
 * @param void
 * @return 0
 */
static uint8_t IMM(void) {
    printf("(MODE) IMM.\n");

    addr_abs = cpu.pc++;
    return 0;
}

/**
 * ZP0: Zero Page Mode. An instruction using zero page addressing mode has only an 8 bit address operand.
 *      This limits it to addressing only the first 256 bytes of memory (e.g. $0000 to $00FF)
 *      where the most significant byte of the address is always zero
 *      --> 0xFF55 can be seen as: FF = Page, 55 = Offset in that page
 * @param void
 * @return 0
 */
static uint8_t ZP0(void) {
    printf("(MODE) ZP0.\n");

    addr_abs = (cpu_fetch() & 0x00FF);
    return 0;
}

/**
 * ZPX: Same mode as ZP0 but this time we add cpu.x to the final address
 * @param void
 * @return 0
 */
static uint8_t ZPX(void) {
    printf("(MODE) ZPX.\n");

    addr_abs = ((cpu_fetch() + cpu.x) & 0x00FF);
    return 0;
}

/**
 * ZPY: Same mode as ZPX but with the cpu.y register instead of x.
 * @param void
 * @return 0
 */
static uint8_t ZPY(void) {
    printf("(MODE) ZPY.\n");

    addr_abs = ((cpu_fetch() + cpu.y) & 0x00FF);
    return 0;
}

/**
 * ABS: Absolute mode. Instructions using this mode contain a full 16 bit address to identify the target location
 * @param void
 * @return
 */
static uint8_t ABS(void) {
    printf("(MODE) ABS.\n");

    uint16_t low = cpu_fetch();
    uint16_t high = cpu_fetch();

    // combine them to form a 16 bit address word
    addr_abs = (high << 8) | low;
    return 0;
}

/**
 * ABX: Same mode as ABS but this time we add cpu.x to the final address.
 * @param void
 * @return 1 if an extra cycles is requires due to page change, 0 if not
 */
static uint8_t ABX(void) {
    printf("(MODE) ABX.\n");

    uint16_t low = cpu_fetch();
    uint16_t high = cpu_fetch();

    // combine them to form a 16 bit address word and add the offset
    addr_abs = (high << 8) | low;
    addr_abs += cpu.x;

    // if the high bytes are different, we have changed page (due to overflow from low to high)
    return ((addr_abs & 0xFF00) != (high << 8)) ? 1 : 0;
}

/**
 * ABY: Same mode as ABX but involving the cpu.y register instead of x
 * @param void
 * @return void
 */
static uint8_t ABY(void) {
    printf("(MODE) ABY.\n");

    uint16_t low = cpu_fetch();
    uint16_t high = cpu_fetch();

    // combine them to form a 16 bit address word and add the offset
    addr_abs = (high << 8) | low;
    addr_abs += cpu.y;

    // if the high bytes are different, we have changed page (due to overflow from low to high)
    return ((addr_abs & 0xFF00) != (high << 8)) ? 1 : 0;
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
    cpu.ac = val;

    return 0;
}

// the populated matrix of opcodes, not a clean solution but it's easily understandable
struct instruction lookup[256] = {
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "LDA", &LDA, &ZP0, 3 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "LDA", &LDA, &IMM, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "LDA", &LDA, &ABS, 4 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "LDA", &LDA, &ZPX, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "LDA", &LDA, &ABY, 4 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "LDA", &LDA, &ABX, 4 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 },
        { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }, { "XXX", &XXX, &IMP, 2 }
};

/**
 * inst_exec: Parse and execute a fetched instruction
 * @param opcode The retrieved opcode from cpu_exec()
 * @param cycles The amount of clock cycles happening
 * @return void
 */
void inst_exec(uint8_t opcode, uint32_t* cycles) {
    fetched_ptr = &opcode;

    *(cycles) = lookup[opcode].cycles;

    (*(lookup[opcode].mode))();
    (*(lookup[opcode].op))();

    debug_print("(inst_exec) cycles: %d, %p\n", *(cycles), (void *)cycles);
}
