/*
 * NOTE: this is meant to be an extension of cpu.c, in fact these two files
 * share the same cpu struct.
 *
 * TODO: check for errors on cpu_fetch()
 * TODO: add missing comments
 */

#include "instructions.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../utils/misc.h"
#include "cpu.h"

/*
 * =============================================
 * MODES PROTOTYPES
 * =============================================
 */

static uint8_t IMP(void);
static uint8_t IMM(void);
static uint8_t ZP0(void);
static uint8_t ZPX(void);
static uint8_t ZPY(void);
static uint8_t ABS(void);
static uint8_t ABX(void);
static uint8_t ABY(void);
static uint8_t IND(void);
static uint8_t IZX(void);
static uint8_t IZY(void);
static uint8_t REL(void);

/*
 * =============================================
 * OPERATIONS PROTOTYPES
 * =============================================
 */

static uint8_t XXX(void);
static uint8_t LDA(void);
static uint8_t LDX(void);
static uint8_t LDY(void);
static uint8_t BRK(void);
static uint8_t BPL(void);
static uint8_t JSR(void);
static uint8_t BMI(void);
static uint8_t RTI(void);
static uint8_t BVC(void);
static uint8_t RTS(void);
static uint8_t BVS(void);
static uint8_t NOP(void);
static uint8_t BCC(void);
static uint8_t BCS(void);
static uint8_t BNE(void);
static uint8_t CPX(void);
static uint8_t CPY(void);
static uint8_t BEQ(void);
static uint8_t ORA(void);
static uint8_t AND(void);
static uint8_t EOR(void);
static uint8_t BIT(void);
static uint8_t ADC(void);
static uint8_t STA(void);
static uint8_t STX(void);
static uint8_t STY(void);
static uint8_t CMP(void);
static uint8_t SBC(void);
static uint8_t ASL(void);
static uint8_t ROL(void);
static uint8_t LSR(void);
static uint8_t ROR(void);
static uint8_t DEC(void);
static uint8_t DEX(void);
static uint8_t DEY(void);
static uint8_t INC(void);
static uint8_t INX(void);
static uint8_t INY(void);
static uint8_t PHP(void);
static uint8_t SEC(void);
static uint8_t CLC(void);
static uint8_t CLI(void);
static uint8_t PLP(void);
static uint8_t PLA(void);
static uint8_t PHA(void);
static uint8_t SEI(void);
static uint8_t TYA(void);
static uint8_t CLV(void);
static uint8_t CLD(void);
static uint8_t SED(void);
static uint8_t TXA(void);
static uint8_t TXS(void);
static uint8_t TAX(void);
static uint8_t TAY(void);
static uint8_t TSX(void);
static uint8_t JMP(void);

// the populated matrix of opcodes, not a clean solution but it's easily
// understandable
struct instruction lookup[256] = {
    {"BRK", &BRK, &IMM, 7}, {"ORA", &ORA, &IZX, 6}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 3}, {"ORA", &ORA, &ZP0, 3},
    {"ASL", &ASL, &ZP0, 5}, {"???", &XXX, &IMP, 5}, {"PHP", &PHP, &IMP, 3},
    {"ORA", &ORA, &IMM, 2}, {"ASL", &ASL, &IMP, 2}, {"???", &XXX, &IMP, 2},
    {"???", &NOP, &IMP, 4}, {"ORA", &ORA, &ABS, 4}, {"ASL", &ASL, &ABS, 6},
    {"???", &XXX, &IMP, 6}, {"BPL", &BPL, &REL, 2}, {"ORA", &ORA, &IZY, 5},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4},
    {"ORA", &ORA, &ZPX, 4}, {"ASL", &ASL, &ZPX, 6}, {"???", &XXX, &IMP, 6},
    {"CLC", &CLC, &IMP, 2}, {"ORA", &ORA, &ABY, 4}, {"???", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4}, {"ORA", &ORA, &ABX, 4},
    {"ASL", &ASL, &ABX, 7}, {"???", &XXX, &IMP, 7}, {"JSR", &JSR, &ABS, 6},
    {"AND", &AND, &IZX, 6}, {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8},
    {"BIT", &BIT, &ZP0, 3}, {"AND", &AND, &ZP0, 3}, {"ROL", &ROL, &ZP0, 5},
    {"???", &XXX, &IMP, 5}, {"PLP", &PLP, &IMP, 4}, {"AND", &AND, &IMM, 2},
    {"ROL", &ROL, &IMP, 2}, {"???", &XXX, &IMP, 2}, {"BIT", &BIT, &ABS, 4},
    {"AND", &AND, &ABS, 4}, {"ROL", &ROL, &ABS, 6}, {"???", &XXX, &IMP, 6},
    {"BMI", &BMI, &REL, 2}, {"AND", &AND, &IZY, 5}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4}, {"AND", &AND, &ZPX, 4},
    {"ROL", &ROL, &ZPX, 6}, {"???", &XXX, &IMP, 6}, {"SEC", &SEC, &IMP, 2},
    {"AND", &AND, &ABY, 4}, {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 7},
    {"???", &NOP, &IMP, 4}, {"AND", &AND, &ABX, 4}, {"ROL", &ROL, &ABX, 7},
    {"???", &XXX, &IMP, 7}, {"RTI", &RTI, &IMP, 6}, {"EOR", &EOR, &IZX, 6},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 3},
    {"EOR", &EOR, &ZP0, 3}, {"LSR", &LSR, &ZP0, 5}, {"???", &XXX, &IMP, 5},
    {"PHA", &PHA, &IMP, 3}, {"EOR", &EOR, &IMM, 2}, {"LSR", &LSR, &IMP, 2},
    {"???", &XXX, &IMP, 2}, {"JMP", &JMP, &ABS, 3}, {"EOR", &EOR, &ABS, 4},
    {"LSR", &LSR, &ABS, 6}, {"???", &XXX, &IMP, 6}, {"BVC", &BVC, &REL, 2},
    {"EOR", &EOR, &IZY, 5}, {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8},
    {"???", &NOP, &IMP, 4}, {"EOR", &EOR, &ZPX, 4}, {"LSR", &LSR, &ZPX, 6},
    {"???", &XXX, &IMP, 6}, {"CLI", &CLI, &IMP, 2}, {"EOR", &EOR, &ABY, 4},
    {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4},
    {"EOR", &EOR, &ABX, 4}, {"LSR", &LSR, &ABX, 7}, {"???", &XXX, &IMP, 7},
    {"RTS", &RTS, &IMP, 6}, {"ADC", &ADC, &IZX, 6}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 3}, {"ADC", &ADC, &ZP0, 3},
    {"ROR", &ROR, &ZP0, 5}, {"???", &XXX, &IMP, 5}, {"PLA", &PLA, &IMP, 4},
    {"ADC", &ADC, &IMM, 2}, {"ROR", &ROR, &IMP, 2}, {"???", &XXX, &IMP, 2},
    {"JMP", &JMP, &IND, 5}, {"ADC", &ADC, &ABS, 4}, {"ROR", &ROR, &ABS, 6},
    {"???", &XXX, &IMP, 6}, {"BVS", &BVS, &REL, 2}, {"ADC", &ADC, &IZY, 5},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4},
    {"ADC", &ADC, &ZPX, 4}, {"ROR", &ROR, &ZPX, 6}, {"???", &XXX, &IMP, 6},
    {"SEI", &SEI, &IMP, 2}, {"ADC", &ADC, &ABY, 4}, {"???", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4}, {"ADC", &ADC, &ABX, 4},
    {"ROR", &ROR, &ABX, 7}, {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 2},
    {"STA", &STA, &IZX, 6}, {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 6},
    {"STY", &STY, &ZP0, 3}, {"STA", &STA, &ZP0, 3}, {"STX", &STX, &ZP0, 3},
    {"???", &XXX, &IMP, 3}, {"DEY", &DEY, &IMP, 2}, {"???", &NOP, &IMP, 2},
    {"TXA", &TXA, &IMP, 2}, {"???", &XXX, &IMP, 2}, {"STY", &STY, &ABS, 4},
    {"STA", &STA, &ABS, 4}, {"STX", &STX, &ABS, 4}, {"???", &XXX, &IMP, 4},
    {"BCC", &BCC, &REL, 2}, {"STA", &STA, &IZY, 6}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 6}, {"STY", &STY, &ZPX, 4}, {"STA", &STA, &ZPX, 4},
    {"STX", &STX, &ZPY, 4}, {"???", &XXX, &IMP, 4}, {"TYA", &TYA, &IMP, 2},
    {"STA", &STA, &ABY, 5}, {"TXS", &TXS, &IMP, 2}, {"???", &XXX, &IMP, 5},
    {"???", &NOP, &IMP, 5}, {"STA", &STA, &ABX, 5}, {"???", &XXX, &IMP, 5},
    {"???", &XXX, &IMP, 5}, {"LDY", &LDY, &IMM, 2}, {"LDA", &LDA, &IZX, 6},
    {"LDX", &LDX, &IMM, 2}, {"???", &XXX, &IMP, 6}, {"LDY", &LDY, &ZP0, 3},
    {"LDA", &LDA, &ZP0, 3}, {"LDX", &LDX, &ZP0, 3}, {"???", &XXX, &IMP, 3},
    {"TAY", &TAY, &IMP, 2}, {"LDA", &LDA, &IMM, 2}, {"TAX", &TAX, &IMP, 2},
    {"???", &XXX, &IMP, 2}, {"LDY", &LDY, &ABS, 4}, {"LDA", &LDA, &ABS, 4},
    {"LDX", &LDX, &ABS, 4}, {"???", &XXX, &IMP, 4}, {"BCS", &BCS, &REL, 2},
    {"LDA", &LDA, &IZY, 5}, {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 5},
    {"LDY", &LDY, &ZPX, 4}, {"LDA", &LDA, &ZPX, 4}, {"LDX", &LDX, &ZPY, 4},
    {"???", &XXX, &IMP, 4}, {"CLV", &CLV, &IMP, 2}, {"LDA", &LDA, &ABY, 4},
    {"TSX", &TSX, &IMP, 2}, {"???", &XXX, &IMP, 4}, {"LDY", &LDY, &ABX, 4},
    {"LDA", &LDA, &ABX, 4}, {"LDX", &LDX, &ABY, 4}, {"???", &XXX, &IMP, 4},
    {"CPY", &CPY, &IMM, 2}, {"CMP", &CMP, &IZX, 6}, {"???", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"CPY", &CPY, &ZP0, 3}, {"CMP", &CMP, &ZP0, 3},
    {"DEC", &DEC, &ZP0, 5}, {"???", &XXX, &IMP, 5}, {"INY", &INY, &IMP, 2},
    {"CMP", &CMP, &IMM, 2}, {"DEX", &DEX, &IMP, 2}, {"???", &XXX, &IMP, 2},
    {"CPY", &CPY, &ABS, 4}, {"CMP", &CMP, &ABS, 4}, {"DEC", &DEC, &ABS, 6},
    {"???", &XXX, &IMP, 6}, {"BNE", &BNE, &REL, 2}, {"CMP", &CMP, &IZY, 5},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4},
    {"CMP", &CMP, &ZPX, 4}, {"DEC", &DEC, &ZPX, 6}, {"???", &XXX, &IMP, 6},
    {"CLD", &CLD, &IMP, 2}, {"CMP", &CMP, &ABY, 4}, {"NOP", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4}, {"CMP", &CMP, &ABX, 4},
    {"DEC", &DEC, &ABX, 7}, {"???", &XXX, &IMP, 7}, {"CPX", &CPX, &IMM, 2},
    {"SBC", &SBC, &IZX, 6}, {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 8},
    {"CPX", &CPX, &ZP0, 3}, {"SBC", &SBC, &ZP0, 3}, {"INC", &INC, &ZP0, 5},
    {"???", &XXX, &IMP, 5}, {"INX", &INX, &IMP, 2}, {"SBC", &SBC, &IMM, 2},
    {"NOP", &NOP, &IMP, 2}, {"???", &SBC, &IMP, 2}, {"CPX", &CPX, &ABS, 4},
    {"SBC", &SBC, &ABS, 4}, {"INC", &INC, &ABS, 6}, {"???", &XXX, &IMP, 6},
    {"BEQ", &BEQ, &REL, 2}, {"SBC", &SBC, &IZY, 5}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4}, {"SBC", &SBC, &ZPX, 4},
    {"INC", &INC, &ZPX, 6}, {"???", &XXX, &IMP, 6}, {"SED", &SED, &IMP, 2},
    {"SBC", &SBC, &ABY, 4}, {"NOP", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 7},
    {"???", &NOP, &IMP, 4}, {"SBC", &SBC, &ABX, 4}, {"INC", &INC, &ABX, 7},
    {"???", &XXX, &IMP, 7},
};

// absolute address in memory
uint16_t addr_abs = 0x0000;

// relative address in memory
uint16_t addr_rel = 0x0000;

uint8_t op = 0x00;
uint32_t* cys = 0x000000;

// a pointer to the fetched opcode in the cpu module
uint8_t fetched = 0x00;

/*
 * =============================================
 * HELPERS
 * =============================================
 */

/**
 * fetch: wrapper around cpu_fetch
 * @param void
 * @return void
 * */
static void fetch(void) {
    if (lookup[op].mode != &IMP) fetched = cpu_fetch(addr_abs);
}

/**
 * branch: executes a branch to defined, see:
 * https://en.wikipedia.org/wiki/Branch_(computer_science)
 *
 * @param void
 * @return void
 * */
static void branch(void) {
    (*cys)++;
    addr_abs = cpu.pc + addr_rel;

    if ((addr_abs & 0xFF00) != (cpu.pc & 0xFF00)) {
        (*cys)++;
    }

    cpu.pc = addr_abs;
    debug_print("(branch) now we are at 0x%X\n", cpu.pc);
}

/**
 * set_flag: sets or unsets corresponding bit in SR depending on the passed
 * expression
 * @param flag the bit you want to set in the SR
 * @param exp boolean that determines the bit status
 * @return void
 * */
static void set_flag(uint8_t flag, bool exp) {
    if (exp) {
        cpu_mod_sr(flag, 1);
    } else {
        cpu_mod_sr(flag, 0);
    }
}

/**
 * reset: actual reset process, must use the cpu_reset wrapper
 * @param void
 * @return void
 * */
void reset(void) {
    addr_abs = 0x8000;

    cpu.pc = addr_abs;
    debug_print("(reset) PC: 0x%X\n", cpu.pc);

    cpu.ac = 0;
    cpu.x = 0;
    cpu.y = 0;
    cpu.sp = 0xFD;
    cpu.sr = 0x00;

    addr_rel = 0x0000;
    addr_abs = 0x0000;
    fetched = 0x00;
}

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
 * @return 0
 */
static uint8_t IMP(void) {
    fetched = cpu.ac;
    return 0;
}

/**
 * IMM: Immediate Mode. Allow the programmer to directly specify an 8-bit
 * constant within the instruction. LDA #10 --> load 10 into the accumulator
 * @param void
 * @return 0
 */
static uint8_t IMM(void) {
    addr_abs = cpu.pc++;
    return 0;
}

/**
 * ZP0: Zero Page Mode. An instruction using zero page addressing mode has only
 * an 8 bit address operand. This limits it to addressing only the first 256
 * bytes of memory (e.g. $0000 to $00FF) where the most significant byte of the
 * address is always zero
 *      --> 0xFF55 can be seen as: FF = Page, 55 = Offset in that page
 * @param void
 * @return 0
 */
static uint8_t ZP0(void) {
    addr_abs = (cpu_fetch(cpu.pc) & 0x00FF);
    return 0;
}

/**
 * ZPX: Same mode as ZP0 but this time we add cpu.x to the final address
 * @param void
 * @return 0
 */
static uint8_t ZPX(void) {
    addr_abs = ((cpu_fetch(cpu.pc) + cpu.x) & 0x00FF);
    return 0;
}

/**
 * ZPY: Same mode as ZPX but with the cpu.y register instead of x.
 * @param void
 * @return 0
 */
static uint8_t ZPY(void) {
    addr_abs = ((cpu_fetch(cpu.pc) + cpu.y) & 0x00FF);
    return 0;
}

/**
 * ABS: Absolute mode. Instructions using this mode contain a full 16 bit
 * address to identify the target location
 * @param void
 * @return
 */
static uint8_t ABS(void) {
    uint16_t low = cpu_fetch(cpu.pc);
    uint16_t high = cpu_fetch(cpu.pc);

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
    uint16_t low = cpu_fetch(cpu.pc);
    uint16_t high = cpu_fetch(cpu.pc);

    // combine them to form a 16 bit address word and add the offset
    addr_abs = (high << 8) | low;
    addr_abs += cpu.x;

    // if the high bytes are different, we have changed page (due to overflow
    // from low to high)
    return ((addr_abs & 0xFF00) != (high << 8)) ? 1 : 0;
}

/**
 * ABY: Same mode as ABX but involving the cpu.y register instead of x
 * @param void
 * @return void
 */
static uint8_t ABY(void) {
    uint16_t low = cpu_fetch(cpu.pc);
    uint16_t high = cpu_fetch(cpu.pc);

    // combine them to form a 16 bit address word and add the offset
    addr_abs = (high << 8) | low;
    addr_abs += cpu.y;

    // if the high bytes are different, we have changed page (due to overflow
    // from low to high)
    return ((addr_abs & 0xFF00) != (high << 8)) ? 1 : 0;
}

/**
 * IND: Indirect mode. 6502 way of implementing pointers.
 *      The only instruction that uses this mode is JMP
 * @param void
 * @return void
 */
static uint8_t IND(void) {
    uint16_t low = cpu_fetch(cpu.pc);
    uint16_t high = cpu_fetch(cpu.pc);

    uint16_t ptr = (high << 8) | low;

    /*
     * If the low byte of the supplied address is 0xFF,
     * then to read the high byte of the actual address
     * we need to cross a page boundary. This doesnt actually work on the chip
     * as designed, instead it wraps back around in the same page, yielding an
     * invalid actual address
     *
     * see: https://www.nesdev.com/6502bugs.txt
     * */
    if (low == 0x00FF) {
        // simulate actual hardware bug!
        addr_abs = (cpu_fetch(ptr & 0xFF00) << 8) | cpu_fetch(ptr + 0);

    } else {
        addr_abs = (cpu_fetch(ptr + 1) << 8) | cpu_fetch(ptr + 0);
    }

    return 0;
}

/**
 * IZX: Indirect addressing of the zero page with X offset
 *      The supplied 8-bit address is offset by X Register to index
 *      a location in page 0x00. The actual 16-bit address is read
 *      from this location.
 * @param void
 * @return void
 */
static uint8_t IZX(void) {
    // reading an address in the zero page
    uint16_t addr_0p = cpu_fetch(cpu.pc);

    uint16_t low = cpu_fetch((uint16_t)(addr_0p + (uint16_t)cpu.x) & 0x00FF);
    uint16_t high =
        cpu_fetch((uint16_t)(addr_0p + (uint16_t)cpu.x + 1) & 0x00FF);

    addr_abs = (high << 8) | low;

    return 0;
}

/**
 * IZY: Indirect addressing of the zero page with Y offset.
 *      Note that this behaves in a different way from the X variation!
 * @param void
 * @return void
 */
static uint8_t IZY(void) {
    uint16_t addr_0p = cpu_fetch(cpu.pc);

    uint16_t low = cpu_fetch(addr_0p & 0x00FF);
    uint16_t high = cpu_fetch((addr_0p + 1) & 0x00FF);

    addr_abs = (high << 8) | low;
    addr_abs += cpu.y;

    return ((addr_abs & 0xFF00) != (high << 8)) ? 1 : 0;
}

/**
 * REL: Relative addressing mode is used by branch instructions which contain a
 * signed 8 bit relative offset (-128 to +127) which is added to cpu.pc if the
 * condition is true.
 * @param void
 * @return void
 */
static uint8_t REL(void) {
    addr_rel = cpu_fetch(cpu.pc);

    // reading a single byte to see if it's signed
    if (addr_rel & 0x80) {
        addr_rel |= 0xFF00;
    }

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
static uint8_t XXX(void) { return 0; }

/**
 * LDA: Load Accumulator
 * @param void
 * @return 1
 */
static uint8_t LDA(void) {
    fetch();
    cpu.ac = fetched;

    set_flag(Z, cpu.ac == 0);
    set_flag(N, cpu.ac & (1 << 7));

    return 1;
}

/**
 * LDX: Load X register
 * @param void
 * @return 1
 */
static uint8_t LDX(void) {
    fetch();
    cpu.x = fetched;

    set_flag(Z, cpu.x == 0);
    set_flag(N, cpu.x & (1 << 7));

    return 1;
}

/**
 * LDY: Load Y register
 * @param void
 * @return 1
 */
static uint8_t LDY(void) {
    fetch();
    cpu.y = fetched;

    set_flag(Z, cpu.y == 0);
    set_flag(N, cpu.y & (1 << 7));

    return 1;
}

static uint8_t BRK(void) {
    cpu.pc++;
    set_flag(I, true);

    cpu_write(0x0100 + cpu.sp, (cpu.pc >> 8) & 0x00FF);
    cpu.sp--;
    cpu_write(0x0100 + cpu.sp, cpu.pc & 0x00FF);
    cpu.sp--;

    set_flag(B, true);
    cpu_write(0x0100 + cpu.sp, cpu.sr);
    cpu.sp--;
    set_flag(B, false);

    cpu.pc = (uint16_t)cpu_fetch(0xFFFE) | ((uint16_t)cpu_fetch(0xFFFF) << 8);
    return 0;
}

static uint8_t JSR(void) {
    cpu.pc--;

    cpu_write(0x0100 + cpu.sp, (cpu.pc >> 8) & 0x00FF);
    cpu.sp--;
    cpu_write(0x0100 + cpu.sp, cpu.pc & 0x00FF);
    cpu.sp--;

    cpu.pc = addr_abs;

    return 0;
}

static uint8_t RTI(void) {
    cpu.sp++;

    cpu.sr = cpu_fetch(0x0100 + cpu.sp);
    cpu.sr &= ~B;

    cpu.sp++;
    cpu.pc = (uint16_t)cpu_fetch(0x0100 + cpu.sp);
    cpu.sp++;
    cpu.pc |= (uint16_t)cpu_fetch(0x0100 + cpu.sp) << 8;

    return 0;
}

static uint8_t RTS(void) {
    cpu.sp++;
    cpu.pc = (uint16_t)cpu_fetch(0x0100 + cpu.sp);
    cpu.sp++;
    cpu.pc |= (uint16_t)cpu_fetch(0x0100 + cpu.sp) << 8;
    cpu.pc++;

    return 0;
}

static uint8_t NOP(void) {
    cpu.pc++;
    return 0;
}

static uint8_t BCC(void) {
    if (cpu_extract_sr(C) == 0) {
        branch();
    }
    return 0;
}

static uint8_t BCS(void) {
    if (cpu_extract_sr(C) == 1) {
        branch();
    }
    return 0;
}

static uint8_t BEQ(void) {
    if (cpu_extract_sr(Z) == 1) {
        branch();
    }
    return 0;
}

static uint8_t BMI(void) {
    if (cpu_extract_sr(N) == 1) {
        branch();
    }
    return 0;
}

static uint8_t BNE(void) {
    if (cpu_extract_sr(Z) == 0) {
        branch();
    }
    return 0;
}

static uint8_t BPL(void) {
    if (cpu_extract_sr(N) == 0) {
        branch();
    }
    return 0;
}

static uint8_t BVC(void) {
    if (cpu_extract_sr(V) == 0) {
        branch();
    }
    return 0;
}

static uint8_t BVS(void) {
    if (cpu_extract_sr(V) == 1) {
        branch();
    }
    return 0;
}

/**
 * CPX: Compare a value in mem to the X register
 * @param void
 * @return 0
 */
static uint8_t CPX(void) {
    fetch();

    // comparing (I think this is just beautiful)
    uint16_t tmp = (uint16_t)cpu.x - (uint16_t)fetched;

    set_flag(C, cpu.x >= fetched);
    set_flag(Z, (tmp & 0x00FF) == 0x0000);
    set_flag(N, tmp & (1 << 7));

    return 0;
}

/**
 * CPY: Compare a value in mem to the Y register
 * @param void
 * @return 0
 */
static uint8_t CPY(void) {
    fetch();

    uint16_t tmp = (uint16_t)cpu.y - (uint16_t)fetched;

    set_flag(C, cpu.y >= fetched);
    set_flag(Z, (tmp & 0x00FF) == 0x0000);
    set_flag(N, tmp & (1 << 7));

    return 0;
}

/**
 * ORA: OR bitwise op on the AC register with a fetched mem value
 * @param void
 * @return 1
 */
static uint8_t ORA(void) {
    fetch();
    cpu.ac = cpu.ac | fetched;

    set_flag(C, cpu.ac == 0);
    set_flag(N, cpu.ac & (1 << 7));

    return 1;
}

/**
 * AND: AND bitwise op on the AC register with a fetched mem value
 * @param void
 * @return 1
 */
static uint8_t AND(void) {
    fetch();
    cpu.ac = cpu.ac & fetched;

    set_flag(C, cpu.ac == 0);
    set_flag(N, cpu.ac & (1 << 7));

    return 1;
}

/**
 * EOR: XOR bitwise op on the AC register with a fetched mem value
 * @param void
 * @return 1
 */
static uint8_t EOR(void) {
    fetch();
    cpu.ac = cpu.ac ^ fetched;

    set_flag(C, cpu.ac == 0);
    set_flag(N, cpu.ac & (1 << 7));

    return 1;
}

static uint8_t BIT(void) {
    fetch();
    uint16_t tmp = cpu.ac & fetched;

    set_flag(Z, (tmp & 0x00F) == 0x00);
    set_flag(N, (fetched & (1 << 7)));
    set_flag(V, (fetched & (1 << 6)));

    return 0;
}

static uint8_t ADC(void) {
    fetch();

    uint16_t tmp =
        (uint16_t)cpu.ac + (uint16_t)fetched + (uint16_t)cpu_extract_sr(C);

    set_flag(C, tmp > 255);
    set_flag(Z, (tmp & 0x00FF) == 0);
    set_flag(V, ((~((uint16_t)cpu.ac ^ (uint16_t)fetched) &
                  ((uint16_t)cpu.ac ^ (uint16_t)tmp)) &
                 0x0080));

    set_flag(N, tmp & 0x0080);

    cpu.ac = tmp & 0x00FF;
    return 1;
}

static uint8_t STA(void) {
    cpu_write(addr_abs, cpu.ac);
    return 0;
}

static uint8_t STX(void) {
    cpu_write(addr_abs, cpu.x);
    return 0;
}

static uint8_t STY(void) {
    cpu_write(addr_abs, cpu.y);
    return 0;
}

static uint8_t CMP(void) {
    fetch();

    // comparing (I think this is just beautiful)
    uint16_t tmp = (uint16_t)cpu.ac - (uint16_t)fetched;

    set_flag(C, cpu.ac >= fetched);
    set_flag(Z, (tmp & 0x00FF) == 0x0000);
    set_flag(N, tmp & (1 << 7));

    return 1;
}

static uint8_t SBC(void) {
    fetch();

    // inverting the bottom 8 bits
    uint16_t val = ((uint16_t)fetched) ^ 0x00FF;

    uint16_t tmp = (uint16_t)cpu.ac + val + (uint16_t)cpu_extract_sr(C);

    set_flag(C, tmp & 0xFF00);
    set_flag(Z, (tmp & 0x00FF) == 0);
    set_flag(V, ((tmp ^ (uint16_t)cpu.ac) & (tmp ^ val) & 0x0080));
    set_flag(N, tmp & 0x0080);

    cpu.ac = tmp & 0x00FF;
    return 1;
}

static uint8_t ASL(void) {
    fetch();
    uint16_t tmp = (uint16_t)fetched << 1;

    set_flag(C, (tmp & 0xFF00) > 0);
    set_flag(Z, (tmp & 0x00FF) == 0x00);
    set_flag(N, tmp & (1 << 7));

    if (lookup[op].mode == &IMP) {
        cpu.ac = tmp & 0x00FF;
    } else {
        cpu_write(addr_abs, tmp & 0x00FF);
    }

    return 0;
}

static uint8_t ROL(void) {
    fetch();
    uint16_t tmp = (uint16_t)(fetched << 1) | cpu_extract_sr(C);

    set_flag(C, tmp & 0xFF00);
    set_flag(Z, (tmp & 0x00FF) == 0x00);
    set_flag(N, tmp & (1 << 7));

    if (lookup[op].mode == &IMP) {
        cpu.ac = tmp & 0x00FF;
    } else {
        cpu_write(addr_abs, tmp & 0x00FF);
    }

    return 0;
}

static uint8_t ROR(void) {
    fetch();
    uint16_t tmp = (uint16_t)(cpu_extract_sr(C) << 7) | (fetched >> 1);

    set_flag(C, fetched & 0x0001);
    set_flag(Z, (tmp & 0x00FF) == 0x00);
    set_flag(N, tmp & (1 << 7));

    if (lookup[op].mode == &IMP) {
        cpu.ac = tmp & 0x00FF;
    } else {
        cpu_write(addr_abs, tmp & 0x00FF);
    }

    return 0;
}

static uint8_t LSR(void) {
    fetch();
    uint16_t tmp = (uint16_t)fetched >> 1;

    set_flag(C, fetched & 0x0001);
    set_flag(Z, (tmp & 0x00FF) == 0x00);
    set_flag(N, tmp & (1 << 7));

    if (lookup[op].mode == &IMP) {
        cpu.ac = tmp & 0x00FF;
    } else {
        cpu_write(addr_abs, tmp & 0x00FF);
    }

    return 0;
}

static uint8_t DEC(void) {
    fetch();
    uint16_t tmp = fetched - 1;

    cpu_write(addr_abs, tmp & 0x00FF);

    set_flag(Z, ((tmp & 0x00FF) == 0x0000));
    set_flag(N, (tmp & (1 << 7)));

    return 0;
}

static uint8_t DEX(void) {
    cpu.x++;

    set_flag(Z, cpu.x == 0x00);
    set_flag(N, cpu.x & (1 << 7));

    return 0;
}

static uint8_t DEY(void) {
    cpu.y--;

    set_flag(Z, cpu.y == 0x00);
    set_flag(N, cpu.y & (1 << 7));

    return 0;
}

static uint8_t INC(void) {
    fetch();
    uint16_t tmp = (uint16_t)fetched + 1;

    cpu_write(addr_abs, tmp & 0x00FF);

    set_flag(Z, ((tmp & 0x00FF) == 0x0000));
    set_flag(N, tmp & (1 << 7));

    return 0;
}

static uint8_t INX(void) {
    cpu.x++;

    set_flag(Z, cpu.x == 0x00);
    set_flag(N, cpu.x & (1 << 7));

    return 0;
}

static uint8_t INY(void) {
    cpu.y++;

    set_flag(Z, cpu.y == 0x00);
    set_flag(N, cpu.y & (1 << 7));

    return 0;
}

static uint8_t PHP(void) {
    cpu_write(0x0100 + cpu.sp, cpu.sr);
    cpu.sp--;

    return 0;
}

static uint8_t SEC(void) {
    set_flag(C, true);
    return 0;
}

static uint8_t CLC(void) {
    set_flag(C, false);
    return 0;
}

static uint8_t PLP(void) {
    cpu.sp++;
    cpu.sr = cpu_fetch(0x0100 + cpu.sp);

    return 0;
}

static uint8_t PLA(void) {
    cpu.sp++;
    cpu.ac = cpu_fetch(0x0100 + cpu.sp);

    set_flag(Z, cpu.ac == 0);
    set_flag(N, cpu.ac & (1 << 7));

    return 0;
}

static uint8_t PHA(void) {
    // 0x0100 is the starting addr of the stack
    cpu_write(0x0100 + cpu.sp, cpu.ac);
    cpu.sp--;

    return 0;
}

static uint8_t CLI(void) {
    set_flag(I, 0);
    return 0;
}

static uint8_t SEI(void) {
    set_flag(I, true);
    return 0;
}

static uint8_t TYA(void) {
    cpu.ac = cpu.y;

    set_flag(Z, cpu.ac == 0);
    set_flag(N, cpu.ac & (1 << 7));

    return 0;
}

static uint8_t CLV(void) {
    set_flag(V, false);
    return 0;
}

static uint8_t CLD(void) {
    set_flag(D, false);
    return 0;
}

static uint8_t SED(void) {
    set_flag(D, true);
    return 0;
}

static uint8_t TXA(void) {
    cpu.ac = cpu.x;

    set_flag(Z, cpu.ac == 0);
    set_flag(N, (cpu.ac & (1 << 7)));

    return 0;
}

static uint8_t TXS(void) {
    cpu.sp = cpu.x;
    return 0;
}

static uint8_t TAX(void) {
    cpu.x = cpu.ac;

    set_flag(Z, cpu.x == 0);
    set_flag(N, (cpu.x & (1 << 7)));

    return 0;
}

static uint8_t TAY(void) {
    cpu.y = cpu.ac;

    set_flag(Z, cpu.y == 0);
    set_flag(N, (cpu.y & (1 << 7)));

    return 0;
}

static uint8_t TSX(void) {
    cpu.x = cpu.sp;

    set_flag(Z, cpu.x == 0);
    set_flag(N, (cpu.x & (1 << 7)));

    return 0;
}

static uint8_t JMP(void) {
    cpu.pc = addr_abs;
    return 0;
}

/**
 * inst_exec: Parse and execute a fetched instruction
 * @param opcode The retrieved opcode from cpu_exec()
 * @param cycles The amount of clock cycles happening
 * @return void
 */
void inst_exec(uint8_t opcode, uint32_t* cycles) {
    // saving variables to the corresponding global ones
    op = opcode;
    cys = cycles;

    *cycles = lookup[opcode].cycles;

    uint8_t additional_cycle_0 = (*(lookup[opcode].mode))();
    uint8_t additional_cycle_1 = (*(lookup[opcode].op))();

    *cycles += (additional_cycle_0 & additional_cycle_1);

    debug_print("(inst_exec) cycles: %d, %p\n", *(cycles), (void*)cycles);
}
