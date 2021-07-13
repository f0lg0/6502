#ifndef INC_6502_KINPUT_H
#define INC_6502_KINPUT_H

#include <stdint.h>

void kinput_listen(void);
uint8_t kinput_should_quit(void);

#endif