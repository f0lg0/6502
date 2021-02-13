#include <SDL2/SDL.h>
#include <stdint.h>
#include "include/interface.h"

SDL_Window* screen;
SDL_Renderer* renderer;

SDL_Scancode keymappings[2] = {
        SDL_SCANCODE_SPACE, SDL_SCANCODE_R
};

uint8_t QUIT = 0;

void inter_init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_CreateWindow("6502", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    // drawing a black bg
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void inter_event_handler(uint8_t* keypad) {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        const Uint8* state = SDL_GetKeyboardState(NULL);

        switch (event.type) {
            case SDL_QUIT:
                QUIT = 1;
                break;
            default:
                if (state[SDL_SCANCODE_ESCAPE]) {
                    QUIT = 1;
                }

                for (uint8_t keycode = 0; keycode < 2; keycode++) {
                    keypad[keycode] = state[keymappings[keycode]];
                }
                break;
        }
    }
}

uint8_t inter_should_quit(void) {
    return QUIT;
}

void inter_stop_display(void) {
    SDL_DestroyWindow(screen);
    SDL_Quit();
}