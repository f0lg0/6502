#ifndef INC_6502_KINPUT_H
#define INC_6502_KINPUT_H

#include <stdint.h>

void kin_tui_listen(void);
uint8_t kin_tui_should_quit(void);

#endif