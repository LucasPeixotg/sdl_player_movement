// std
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "constants.h"
#include "player.h"


// outside variables
extern Player player;

// global variables
int game_is_running = FALSE;


/*
    Initializes EVERYTHIG from SDL and creates a window

    returns: 0 if could not initialize something,
             1 if it was successful
*/
int initialize_window(SDL_Window** window, SDL_Renderer** renderer) {
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    *window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS 
    );
    if(!*window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return FALSE;
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if(!*renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void setup(void) {
    setup_player();
}

void process_inputs() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) game_is_running = FALSE;

            if(event.key.keysym.sym == SDLK_w) player.move_set.up = TRUE;
            if(event.key.keysym.sym == SDLK_d) player.move_set.right = TRUE;
            if(event.key.keysym.sym == SDLK_s) player.move_set.down = TRUE;
            if(event.key.keysym.sym == SDLK_a) player.move_set.left = TRUE;
            if(event.key.keysym.sym == SDLK_SPACE) player.move_set.dash = TRUE;

            break;
        case SDL_KEYUP:
            if(event.key.keysym.sym == SDLK_w) player.move_set.up = FALSE;
            if(event.key.keysym.sym == SDLK_d) player.move_set.right = FALSE;
            if(event.key.keysym.sym == SDLK_s) player.move_set.down = FALSE;
            if(event.key.keysym.sym == SDLK_a) player.move_set.left = FALSE;
            if(event.key.keysym.sym == SDLK_SPACE) player.move_set.dash = FALSE;

            break;

    }
}

void update() {
    update_player();
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
    SDL_RenderClear(renderer);

    render_player(renderer);

    // buffer swap
    SDL_RenderPresent(renderer);
}

int main(void) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    game_is_running = initialize_window(&window, &renderer);

    setup();
    while(game_is_running) {
        process_inputs();
        update();
        render(renderer);
    }
}