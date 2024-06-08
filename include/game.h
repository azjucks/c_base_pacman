#ifndef __GAME__
#define __GAME__

#include <stdbool.h>

#include "input.h"
#include "player.h"
#include "draw.h"
#include "board.h"
#include "enemy.h"
#include "defs.h"

typedef struct game_s
{
    int screen_width;
    int screen_height;
    int mid_ref_width;
    int mid_ref_height;

    draw_t* draw;

    board_t* board;

    input_t* input;
    player_t* player;
    
    enemy_t* enemies;

	int current_score;
	int high_score;
} game_t;


game_t*     create_game();
void        reset_game(game_t* game);
void        destroy_game(game_t* game);


void        game_main_loop(game_t* game);

#endif
