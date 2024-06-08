#include "board.h"
#include "map.h"
#include "game.h"

#include <stdlib.h>

board_t* create_board(game_t* game)
{
	board_t* board = malloc(sizeof(board_t));
	
	init_board(board, game);
	
	return board;
}

void destroy_board(board_t* board)
{
	free(board->cells);
	free(board);
}

void init_board(board_t* board, game_t* game)
{
	board->width = BOARD_WIDTH;
	board->height = BOARD_HEIGHT;

	SDL_Surface* surface = IMG_Load("assets/pac man tiles/background_hd_2.png");
	if (surface == NULL)
		return;

	board->tileset = utils_load_texture(game->draw->renderer, surface);
	
	board->cells = malloc(board->width * board->height * sizeof(cell_t));
	
	read_map_file("map/board.map", board, game);

	set_tile_cell_sprite(board);
}

int screen_to_board(int x)
{
    return x / UNIT_SIZE;
}

int board_to_screen(int x)
{
    return x * UNIT_SIZE;
}
