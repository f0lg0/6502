#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>

#include "interface.h"

SDL_Window* screen;
SDL_Renderer* renderer;
TTF_Font* font;
SDL_Surface* surface_msg;
SDL_Texture* msg;
SDL_Rect msg_rect;

SDL_Scancode keymappings[2] = {
        SDL_SCANCODE_SPACE, SDL_SCANCODE_R
};

uint8_t QUIT = 0;

void inter_init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_CreateWindow("6502", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void inter_init_text(char* str) {
    TTF_Init();

    font = TTF_OpenFont("../assets/retro.ttf", 24);

    if (font == NULL) {
        printf("(FAILED) Cannot load font set.\n");
        exit(1);
    }

    // TODO: move this to a dedicated function so I can draw arbitrary text without  initializing everything everytime

    SDL_Color white = {255, 255, 255, 255};
    surface_msg = TTF_RenderText_Solid(font, str, white);

    if (surface_msg == NULL) {
        printf("(FAILED) Can't create surface.\n");
        exit(1);
    }

    msg = SDL_CreateTextureFromSurface(renderer, surface_msg);

    if (msg == NULL) {
        printf("(FAILED) Can't create texture.\n");
        exit(1);
    }

    msg_rect.x = 0;
    msg_rect.y = 0;
    msg_rect.w = W_WIDTH / 2;
    msg_rect.h = 40;
}

void inter_draw(void) {
    // drawing black bg
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if ((SDL_RenderCopy(renderer, msg, NULL, &msg_rect)) == -1) {
        printf("(FAILED) Can't render text.\n");
        exit(1);
    }

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

            case SDL_KEYDOWN:
                for (uint8_t keycode = 0; keycode < 2; keycode++) {
                    keypad[keycode] = state[keymappings[keycode]];
                }
                break;

            default:
                if (state[SDL_SCANCODE_ESCAPE]) {
                    QUIT = 1;
                }
                break;
        }
    }
}



uint8_t inter_should_quit(void) {
    return QUIT;
}

void inter_stop_display(void) {
    SDL_FreeSurface(surface_msg);
    SDL_DestroyTexture(msg);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(screen);
    SDL_Quit();
}
