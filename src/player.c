// std
#include <math.h>
#include <SDL2/SDL.h>

#include "constants.h"
#include "gametime.h"
#include "utils.h"
#include "player.h"

Player player;

void setup_player(void) {
    player.width = PLAYER_WIDTH;
    player.height = PLAYER_HEIGHT;

    player.x = WINDOW_WIDTH / 2.0f - player.width / 2.0f;
    player.y = WINDOW_HEIGHT / 2.0f - player.height / 2.0f;
    
    player.direction[0] = 0;
    player.direction[1] = 0;
    
    player.velocity = 0;
    player.acceleration = 0;
    player.friction = PLAYER_DEFAULT_FRICTION;

    player.move_set.up    = FALSE;
    player.move_set.right = FALSE;
    player.move_set.down  = FALSE;
    player.move_set.left  = FALSE;
    player.move_set.dash  = FALSE;
    
    player.possible_moves.up    = TRUE;
    player.possible_moves.right = TRUE;
    player.possible_moves.down  = TRUE;
    player.possible_moves.left  = TRUE;
    player.possible_moves.dash  = TRUE;
}

void set_move_player(void) {
    static Uint32 move_ticks_start = 0;

    if(player.move_set.right && player.possible_moves.right) {
        player.direction[0] = 1;
    } else if(player.move_set.left && player.possible_moves.left) {
        player.direction[0] = -1;
    }

    if(player.move_set.up && player.possible_moves.up) {
        player.direction[1] = -1;
    } else if(player.move_set.down && player.possible_moves.down) {
        player.direction[1] = 1;
    }

    if(!player.move_set.up && !player.move_set.right && !player.move_set.down && !player.move_set.left) {
        player.acceleration = 0;
    } else if(!player.is_dashing) {
        normalize_vector2(player.direction);
        player.acceleration = PLAYER_ACCELERATION;

        if(player.move_set.dash) {
            if(player.possible_moves.dash) {
                player.possible_moves.up    = FALSE;
                player.possible_moves.right = FALSE; 
                player.possible_moves.down  = FALSE;  
                player.possible_moves.left  = FALSE;
                player.possible_moves.dash  = FALSE;  

                player.is_dashing = TRUE;
                move_ticks_start = SDL_GetTicks();

                player.direction[0] *= PLAYER_DASH_FACTOR;
                player.direction[1] *= PLAYER_DASH_FACTOR;
            }
        }
    }

    float seconds = get_delta_since(move_ticks_start);

    if(player.is_dashing) {
        if(seconds >= PLAYER_DASH_DURATION) {
            player.is_dashing = FALSE;
            player.is_dashing_delay = TRUE;

            player.possible_moves.up    = TRUE;
            player.possible_moves.right = TRUE; 
            player.possible_moves.down  = TRUE;  
            player.possible_moves.left  = TRUE;  
            
            normalize_vector2(player.direction);
            move_ticks_start = SDL_GetTicks();
        }
    }

    if(player.is_dashing_delay) {
        if(seconds >= PLAYER_DASH_DELAY) {
            player.possible_moves.dash  = TRUE;
            player.is_dashing_delay = FALSE;
        }
    }
}

void update_player(void) {
    set_move_player();

    float delta_time = get_delta_time();

    if(player.velocity < PLAYER_MAX_SPEED) {
        player.velocity += player.acceleration * delta_time;
        if(player.velocity > PLAYER_MAX_SPEED) player.velocity = PLAYER_MAX_SPEED;
    }

    player.x += player.direction[0] * player.velocity * delta_time;
    player.y += player.direction[1] * player.velocity * delta_time;

    if(player.acceleration == 0) {
        player.velocity -= player.friction * delta_time;
        if(player.velocity < 0) player.velocity = 0;
    }
}

void render_player(SDL_Renderer* renderer) {
    SDL_Rect player_rect = {
        (int) player.x,
        (int) player.y,
        (int) player.width,
        (int) player.height
    };

    if(player.is_dashing) {
        SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
    } else if(player.possible_moves.dash) {
        SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    }
    SDL_RenderFillRect(renderer, &player_rect);
}
