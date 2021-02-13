#include <stdint.h>

#include "include/kinput.h"
#include "include/interface.h"
#include "include/cpu.h"

// keypad representing the keyboard
uint8_t keypad[2] = {0};
uint8_t ksize = 2;

/**
 * kin_clear_keypad: Re-set the keypad to the 0 state, meaning nothing is pressed
 * @param void
 * @return void
 */
static void kin_clear_keypad(void) {
    for (uint8_t i = 0; i < ksize; i++) {
        keypad[i] = 0;
    }
}

/**
 * kin_start: Initialize the input module and parse key presses
 * @param void
 * @return void
 */
void kin_start(void) {
    inter_event_handler(keypad);

    if (keypad[SPACE]) {
        cpu_exec();
    } else if (keypad[R]) {
        cpu_reset();
    }

    kin_clear_keypad();
}

