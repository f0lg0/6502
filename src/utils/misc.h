#ifndef UTILS_H
#define UTILS_H

#define debug_print(fmt, ...)                         \
    do {                                              \
        if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); \
    } while (0)

extern uint8_t DEBUG;

#define SET_BIT(val, pos) (val |= (1U << pos))
#define CLEAR_BIT(val, pos) (val &= (~(1U << pos)))


#endif
