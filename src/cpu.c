#include <stdint.h>
#include <stdio.h>

#include "include/cpu.h"
#include "include/mem.h"
#include "include/instructions.h"
#include "utils/misc.h"

/**
 * Little-endian 8-bit microprocessor that expects addresses
 * to be store in memory least significant byte first
 * */
struct central_processing_unit cpu;

// clock cycles, every fetch implies a clock cycle
uint32_t cycles = 0;

struct mem* mem_ptr = NULL;

/**
 * cpu_init: Initialize CPU by linking it to the memory
 * @param void
 * @return void
 */
void cpu_init(void) {
    mem_ptr = mem_get_ptr();
}

/**
 * cpu_extract_sr: Extract one of the 7 flags from the status reg.
 * @param flag The flag to be extracted
 * @return the bit of the wanted flag
 * */
uint8_t cpu_extract_sr(uint8_t flag) { return ((cpu.sr >> (flag % 8)) & 1); }

/**
 * cpu_mod_sr: Modify the sr register (flags)
 * @param flag The flag to set
 * @param val The value
 * @return 0 if success, 1 if failure
 */
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
    printf("(cpu_reset) called.\n");

    cpu.pc = 0x200;
    cpu.sp = 0xFD;
    cpu.ac = 0x00;
    cpu.x = 0x00;
    cpu.y = 0x00;
    cpu.sr = 0x00;

    cycles = 8;
}

/**
 * get_mem: Wrapper to handle memory accessing, due to the pages being separated
 * @param addr The address we want to access
 * @return The retrieved data
 */
static uint8_t get_mem(uint32_t addr) {
    uint8_t parsed = 0;

    // no need to check >= 0x0000, it's unsigned
    if (addr <= 0x00FF) {
        return mem_ptr->zero_page[addr];
    } else if (addr >= 0x0100 && addr <= 0x01FF) {
        parsed = addr - 0x0100;
        return mem_ptr->stack[parsed];
    } else if (addr >= 0xFFFA && addr <= 0xFFFF) {
        parsed = addr - 0xFDFA;
        return mem_ptr->last_six[parsed];
    } else {
        parsed = addr - 0x0200;
        return mem_ptr->data[parsed];
    }
}

/**
 * cpu_fetch: Fetch from memory
 * @param void
 * @return void
 */
uint8_t cpu_fetch() {
    uint8_t data = get_mem(cpu.pc);
    cpu.pc++;

    return data;
}

/**
 * cpu_exec: Execute fetched data (single stepping)
 * @param void
 * @return void
 */
void cpu_exec() {
    printf("(cpu_exec) cycles: %d, mem: %p\n", cycles, (void*)mem_ptr);

    uint8_t fetched = 0x00;
    do {
        printf("(loop) cycles: %d\n", cycles);
        // executing in a take
        if (cycles == 0) {
            fetched = cpu_fetch(mem_ptr);
            printf("(cpu_exec) fetched: 0x%X\n", fetched);
            inst_exec(fetched, &cycles);
        }
        cycles--;
    } while (cycles != 0);
}
