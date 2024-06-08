#include "draw.h"
#include "defs.h"
#include "game.h"
#include "board.h"
#include "string_length.h"
#include "string_sized_concatenate.h"
#include "string_duplicate.h"
#include "int_to_alpha.h"

#include <SDL2/SDL_ttf.h>

const int unit_half = UNIT_SIZE / 2;


draw_t* create_draw(game_t* game)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	utils_init_window_and_renderer(game, &window, &renderer);
	
	draw_t* draw = malloc(sizeof(draw_t));
	
	draw->window = window;
	draw->renderer = renderer;

	return draw;
}

void draw_debug_player(game_t* game)
{
	SDL_SetRenderDrawColor(game->draw->renderer, 255, 0, 0, 255);
	SDL_Rect rect = {game->player->x - unit_half / 2, game->player->y - unit_half / 2, UNIT_SIZE / 2, UNIT_SIZE / 2};
	SDL_RenderDrawRect(game->draw->renderer, &rect);

	SDL_SetRenderDrawColor(game->draw->renderer, 0, 255, 0, 255);
	SDL_Rect rect1 = {game->player->destX - unit_half / 1.6f, game->player->destY - unit_half / 1.6f, UNIT_SIZE / 1.6f, UNIT_SIZE / 1.6f};
	SDL_RenderDrawRect(game->draw->renderer, &rect1);

	SDL_SetRenderDrawColor(game->draw->renderer, 250, 80, 0, 255);
	SDL_Rect rect2 = {game->player->destX - unit_half, game->player->destY - unit_half, UNIT_SIZE, UNIT_SIZE};
	SDL_RenderDrawRect(game->draw->renderer, &rect2);
}

void draw_debug(game_t* game)
{
	draw_debug_player(game);

    TTF_Font* font = TTF_OpenFont("assets/fonts/JetBrainsMono-Medium.ttf", 16);
	SDL_Color White = {255, 255, 255, 255};

    char* temp = "Player score: ";
	
	char* speed_txt = int_to_alpha(game->player->score);

	
	int speed_txt_size = string_length(speed_txt);
	
	char* player_text = string_duplicate(temp);
	
	player_text = realloc(player_text, (string_length(temp) + speed_txt_size) * sizeof(char));
	
	string_sized_concatenate(player_text, speed_txt, speed_txt_size);
	
	int player_vel_size = string_length(player_text);
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, player_text, White);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->draw->renderer, surface);
	
	SDL_Rect rect = {0, SCREEN_HEIGHT - 32, 16 * player_vel_size, 16};
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void draw_board(game_t* game, Uint32 item_render_frequency)
{
	board_t* board = game->board;
	
	for (int i = 0; i < board->height; ++i)
	{
		for (int j = 0; j < board->width; ++j)
		{
			if(board->cells[j + i * board->width].is_wall)
			{
				utils_cell_render_cpy(game, board, board->cells[j + i * board->width],
										board_to_screen(j),
										board_to_screen(i));
			}
			else
			{
				utils_item_render_cpy(game, board->cells[j + i * board->width].item,
										board_to_screen(j),
										board_to_screen(i), item_render_frequency);
			}
		}
	}
}

void draw_player(game_t* game, Uint32 player_render_frequency)
{
	utils_entity_render_cpy(game, game->player, player_render_frequency);
}
