#include <SDL2/SDL.h>

typedef struct {
    int up;
    int right;
    int down;
    int left;
    int dash;
} MoveSet;

typedef struct {
    float x;
    float y;
    float direction[2];
    float width;
    float height;
    float velocity;
    float acceleration;
    float friction;
    float angle;
    MoveSet move_set;
    MoveSet possible_moves;
    int is_dashing;
    int is_dashing_delay;
} Player;


void update_player();

void render_player(SDL_Renderer* renderer);

void setup_player(void);

void set_move_player();

void rotate_player(int x, int y);