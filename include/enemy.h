#ifndef __ENEMY__
#define __ENEMY__

#include "sdl_utils.h"

typedef struct enemy_s
{
	tile_t* tile;
	
    int x;
    int y;

    float speed;
} enemy_t;


enemy_t* create_enemy_list();

#endif
