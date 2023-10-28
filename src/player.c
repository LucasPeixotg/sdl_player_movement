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

    player.move_set.up    = FALSE;
    player.move_set.right = FALSE;
    player.move_set.down  = FALSE;
    player.move_set.left  = FALSE;
}

void set_move_player(void) {
    if(player.move_set.right) {
        player.direction[0] = 1;
    } else if(player.move_set.left) {
        player.direction[0] = -1;
    } else {
        player.direction[0] = 0;
    }

    if(player.move_set.up) {
        player.direction[1] = -1;
    } else if(player.move_set.down) {
        player.direction[1] = 1;
    } else {
        player.direction[1] = 0;
    }

    if(player.direction[0] == 0 && player.direction[1] == 0) player.velocity = 0;
    else {
        normalize_vector2(player.direction);
        player.velocity = PLAYER_MOVE_SPEED;
    }
}

void update_player(void) {
    set_move_player();

    float delta_time = get_delta_time();

    player.x += player.direction[0] * player.velocity * delta_time;
    player.y += player.direction[1] * player.velocity * delta_time;

}

void render_player(SDL_Renderer* renderer) {
    SDL_Rect player_rect = {
        (int) player.x,
        (int) player.y,
        (int) player.width,
        (int) player.height
    };

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &player_rect);
}
