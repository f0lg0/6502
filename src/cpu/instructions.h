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

extern struct instruction lookup[256];

/*
 * =============================================
 * MODES
 * =============================================
 */

uint8_t IMP(void);
uint8_t IMM(void);
uint8_t ZP0(void);
uint8_t ZPX(void);
uint8_t ZPY(void);
uint8_t ABS(void);
uint8_t ABX(void);
uint8_t ABY(void);
uint8_t IND(void);
uint8_t IZX(void);
uint8_t IZY(void);
uint8_t REL(void);

/*
 * =============================================
 * OPERATIONS
 * =============================================
 */

uint8_t XXX(void);
uint8_t LDA(void);
uint8_t LDX(void);
uint8_t LDY(void);
uint8_t BRK(void);
uint8_t BPL(void);
uint8_t JSR(void);
uint8_t BMI(void);
uint8_t RTI(void);
uint8_t BVC(void);
uint8_t RTS(void);
uint8_t BVS(void);
uint8_t NOP(void);
uint8_t BCC(void);
uint8_t BCS(void);
uint8_t BNE(void);
uint8_t CPX(void);
uint8_t CPY(void);
uint8_t BEQ(void);
uint8_t ORA(void);
uint8_t AND(void);
uint8_t EOR(void);
uint8_t BIT(void);
uint8_t ADC(void);
uint8_t STA(void);
uint8_t STX(void);
uint8_t STY(void);
uint8_t CMP(void);
uint8_t SBC(void);
uint8_t ASL(void);
uint8_t ROL(void);
uint8_t LSR(void);
uint8_t ROR(void);
uint8_t DEC(void);
uint8_t DEX(void);
uint8_t DEY(void);
uint8_t INC(void);
uint8_t INX(void);
uint8_t INY(void);
uint8_t PHP(void);
uint8_t SEC(void);
uint8_t CLC(void);
uint8_t CLI(void);
uint8_t PLP(void);
uint8_t PLA(void);
uint8_t PHA(void);
uint8_t SEI(void);
uint8_t TYA(void);
uint8_t CLV(void);
uint8_t CLD(void);
uint8_t SED(void);
uint8_t TXA(void);
uint8_t TXS(void);
uint8_t TAX(void);
uint8_t TAY(void);
uint8_t TSX(void);
uint8_t JMP(void);

void inst_exec(uint8_t opcode, uint32_t* cycles);

#endif
