#ifndef INC_6502_INTERFACE_H
#define INC_6502_INTERFACE_H

#include <stdint.h>
#define W_WIDTH 640
#define W_HEIGHT 480

void inter_init_display(void);
void inter_event_handler(uint8_t* keypad);
uint8_t inter_should_quit(void);
void inter_stop_display(void);
void inter_init_text();
void inter_draw(void);

#endif
