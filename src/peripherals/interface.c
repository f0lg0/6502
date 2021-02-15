/*
 * NOTE: this module is trash. I am not a game/graphics developer, this
 * is my first time creating a GUI for a program (I only have experience in web-dev).
 * I am interested in feedback regarding graphics performance, I know there are some
 * cool techniques but I want to focus more on the 6502 itself.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdio.h>

#include "interface.h"
#include "../cpu/cpu.h"

SDL_Window* screen;
SDL_Renderer* renderer;
TTF_Font* font;

// header
SDL_Surface* header_surface;
SDL_Texture* header;
SDL_Rect header_rect;

// registers
SDL_Surface* regs_surface;
SDL_Texture* regs;
SDL_Rect regs_rect;

SDL_Scancode keymappings[2] = {
        SDL_SCANCODE_SPACE, SDL_SCANCODE_R
};

uint8_t QUIT = 0;

void inter_init_display(void) {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_CreateWindow("6502", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

static void display_header(void) {
    SDL_Color white = {255, 255, 255, 255};
    header_surface = TTF_RenderText_Solid(font, "6502 Emulator", white);

    if (header_surface == NULL) {
        printf("(FAILED) Can't create surface.\n");
        exit(1);
    }

    header = SDL_CreateTextureFromSurface(renderer, header_surface);

    if (header == NULL) {
        printf("(FAILED) Can't create texture.\n");
        exit(1);
    }

    header_rect.y = 0;
    header_rect.w = W_WIDTH / 2;
    header_rect.x = 0;
    header_rect.h = 40;
}

static void destroy_header(void) {
    SDL_FreeSurface(header_surface);
    SDL_DestroyTexture(header);
}

static void display_registers(void) {
    // is this even secure? lol
    // MAX STRING WE CAN POSSIBLY GET --> ac: 255\npc: 65535\nsp: 255\nx: 255\ny: 255\nsr: 255
    uint16_t max_str_len = strlen("ac: 255 pc: 65535 sp: 255 x: 255 y: 255 sr: 255");
    char* buff = malloc(max_str_len + 1);

    if ((snprintf(buff, max_str_len, "ac: %d pc: %d sp: %d x: %d y: %d sr: %d", cpu.ac, cpu.pc,  cpu.sp, cpu.x, cpu.y, cpu.sr)) < 0) {
        printf("(FAILED) Can't format string into buffer.\n");
        exit(1);
    }

    SDL_Color white = {255, 0, 0, 255};
    regs_surface = TTF_RenderText_Solid(font, buff, white);

    if (regs_surface == NULL) {
        printf("(FAILED) Can't create surface.\n");
        exit(1);
    }

    regs = SDL_CreateTextureFromSurface(renderer, regs_surface);

    if (regs == NULL) {
        printf("(FAILED) Can't create texture.\n");
        exit(1);
    }

    regs_rect.y = 50;
    regs_rect.w = W_WIDTH - 10;
    regs_rect.x = 0;
    regs_rect.h = 20;

    free(buff);
}

static void destroy_registers(void) {
    SDL_FreeSurface(regs_surface);
    SDL_DestroyTexture(regs);
}

void inter_init_text(void) {
    TTF_Init();

    font = TTF_OpenFont("../assets/retro.ttf", 24);

    if (font == NULL) {
        printf("(FAILED) Cannot load font set.\n");
        exit(1);
    }

    display_header();
    display_registers();
}

void inter_draw(void) {
    // drawing black bg
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int8_t status;

    status = SDL_RenderCopy(renderer, header, NULL, &header_rect);

    if (status == -1) {
        printf("(FAILED) Can't render text.\n");
        exit(1);
    }

    // TODO: make this better (maybe an update function). Avoid re-creating everything here
    display_registers();

    status = SDL_RenderCopy(renderer, regs, NULL, &regs_rect);

    if (status == -1) {
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
    // destroying texts
    destroy_header();
    destroy_registers();

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(screen);
    SDL_Quit();
}
