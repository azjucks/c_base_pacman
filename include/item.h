#ifndef __ITEM_H_
#define __ITEM_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "sdl_utils.h"


typedef struct game_s game_t;

typedef enum
{
	E_PILL,
	E_BIG_PILL,
	E_WARP,
	E_NONE,
	
	E_COUNT
}E_ITEM;

typedef struct item_s
{
	tile_t tile;
	
	SDL_Texture* sprite;

	E_ITEM item_type;

	int score;
}item_t;

void init_item(game_t* game, item_t* item, E_ITEM item_type, int score);

void destroy_item(item_t* item);

#endif