#ifndef INC_6502_INTERFACE_H
#define INC_6502_INTERFACE_H

#include <stdint.h>

void inter_init_display(void);
void inter_event_handler(uint8_t* keypad);
uint8_t inter_should_quit(void);
void inter_stop_display(void);
void inter_render_text(char* str);

#endif