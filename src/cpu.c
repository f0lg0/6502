#include "include/cpu.h"

#include <stdint.h>
#include <stdio.h>

#include "include/mem.h"
#include "utils/misc.h"

/**
 * Little-endian 8-bit microprocessor that expects addresses
 * to be store in memory least significant byte first
 * */
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
} cpu;

/**
 * cpu_extract_sr: Extract one of the 7 flags from the status reg.
 *
 * @param the flag to be extracted
 * @return the bit of the wanted flag
 * */
uint8_t cpu_extract_sr(uint8_t flag) { return ((cpu.sr >> (flag % 8)) & 1); }

uint8_t cpu_mod_sr(uint8_t flag, uint8_t val) {
    if (val != 0 && val != 1) return 1;

    if (flag > 0 && flag < 8 && flag != 5) {
        if (val == 1) {
            SET_BIT(cpu.sr, flag);
        } else {
            CLEAR_BIT(cpu.sr, flag);
        }
        return 0;
    } else {
        return 1;
    }
}

/**
 * cpu_reset: Reset the CPU to its initial state.
 *            There are different initial states for different
 *            machines, see like the reset process in the C64.
 *            At the moment I am setting everything to 0.
 *
 * @param void
 * @return void
 * */
void cpu_reset(void) {
    cpu.pc = 0;
    cpu.sp = 0;
    cpu.sp = 0;
    cpu.x = 0;
    cpu.y = 0;
    cpu.sr = 0;
}

// TODO: IMPORTANT, addresses in the pages are different from the general addr.
static uint8_t get_mem(uint32_t addr, struct mem* mem_ptr) {
    uint8_t parsed = 0;

    if (addr >= 0x0000 && addr <= 0x00FF) {
        return mem_ptr->zero_page[addr];
    } else if (addr >= 0x0100 && addr <= 0x01FF) {
        parsed = addr - 0x0100;
        return mem_ptr->stack[parsed];
    } else if (addr >= 0xFFFA && addr <= 0xFFFF) {
        parsed = addr - 0xFDFA;
        return mem_ptr->last_six[parsed];
    } else {
        parsed = addr - 0x0200
        return mem_ptr->data[parsed];
    }
}

uint8_t cpu_fetch(uint32_t* cycles, struct mem* mem_ptr) {
    uint8_t data = get_mem(cpu.pc, mem_ptr); 
    cpu.pc++;
    cycles--;

    return data;
}

void cpu_exec(uint32_t cycles, struct mem* mem_ptr) {
    printf("(cpu_exec) cycles: %d, mem: %p\n", cycles, (void*)mem_ptr);
    uint8_t fetched = cpu_fetch(&cycles, mem_ptr);
    printf("(cpu_exec) fetched: 0x%X\n", fetched);
}
