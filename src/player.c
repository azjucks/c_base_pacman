#include "player.h"

#include "game.h"



#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>


player_t* create_player(game_t* game)
{
    // PLAYER CREATION
    player_t* player = malloc(sizeof(player_t));
 	
    player->x = board_to_screen(PLAYER_START_X) - UNIT_SIZE / 2;
    player->y = board_to_screen(PLAYER_START_Y);
    
    player->destX = player->x;
    player->destY = player->y;
    player->newdestX = player->x;
    player->newdestY = player->y;
    
    player->speed = PLAYER_SPEED;

    player->dir = NONE;
    player->newdir = NONE;

    // SPRITE CREATION
    // NEED TO BE PUT IN ANOTHER FUNCTION !!!

	tile_t tile = {};
	
	tile.width = UNIT_SIZE * 2;
	tile.height = UNIT_SIZE * 2;
	tile.row = 0;
	tile.column = 0;
	
	player->tile = tile;
	
	player->score = 0;
    player->warp = false;

	SDL_Surface* surface = IMG_Load("assets/pac man & life counter & death/pac man/pac_man_sheet.png");
	if (surface == NULL)
		return NULL;
	
	player->sprite = utils_load_texture(game->draw->renderer, surface);
	
	SDL_FreeSurface(surface);

	return player;
}

void destroy_player(player_t* player)
{
	SDL_DestroyTexture(player->sprite);
    free(player);
}


void player_process(game_t* game, float deltaTicks)
{
    board_t* board = game->board;
    input_t* input = game->input;
    player_t* player = game->player; 

    
    

    // Puts input direction into newdir and newdest
    player_update_direction(board, input->dir, player);            

    

    // if we can move forward
    if (player_check_destination(player))
    {
        // move by velocity
        float velocity = player->speed * deltaTicks;
        player_update_position(player, velocity);
    }
    else
    {
        player_check_cell(game);
        
        player->x = player->destX;
        player->y = player->destY;     
    }  
	
    if (!player_check_destination(player))
    {
        player_check_cell(game);

        if (player->dir == player->newdir)
            player_update_direction(board, player->dir, player);
        
        player->dir = player->newdir;
        player->destX = player->newdestX;
        player->destY = player->newdestY;
    }
    
    
    // DEBUG
    //printf("POSX = %f && DESTX = %i \n", (player->x), (player->destX));
}


void player_check_cell(game_t* game)
{
    board_t* board = game->board;
    player_t* player = game->player;

    int x = screen_to_board(player->destX);
    int y = screen_to_board(player->destY);

    cell_t* cell = &board->cells[x + y * board->width];
	
    player_cell_process(player, cell);
}

void player_cell_process(player_t* player, cell_t* cell)
{
    item_t* item = &cell->item;

    //if (item->item_type == E_WARP)
        //printf("%i\n", item->item_type == E_WARP);

    //printf("%i\n", screen_to_board(player->x));

    switch(item->item_type)
    {
        case E_PILL:
            player->score += item->score;
            destroy_item(item);
            break;
        case E_BIG_PILL:
            player->score += item->score;
            destroy_item(item);
            break;
        case E_WARP:
            if (!player->warp)
            {
                player->warp = true;
                if (screen_to_board(player->x) < 1)
                {
                    player->x = board_to_screen(BOARD_WIDTH);
                    player->destX = player->x;
                }
                else
                {
                    player->x = board_to_screen(0);
                    player->destX = player->x;
                }
            }
            break;
        default:
            player->warp = false;
            break;
    }
}


bool player_check_destination(player_t* player)
{
    if (player->dir == NONE)
        player->dir = player->newdir;

    switch(player->dir)
    {
        case UP:
            return player->y > player->destY;
        case DOWN:
            return player->y < player->destY;
        case LEFT:
            return player->x > player->destX;
        case RIGHT:
            return player->x < player->destX;
        default:
            break;
    }
    return false;
}



void player_update_direction(board_t* board, E_DIR dir, player_t* player)
{
    int x = screen_to_board(player->destX);
    int y = screen_to_board(player->destY);

    //printf("x = %i & y = %i\n", x, y);

    switch(dir)
    {
        case UP:
            if (y > 0 && !board->cells[x + (y - 1) * board->width].is_wall)
            {                         
                player->newdir = UP;
                player->newdestX = board_to_screen(x);      
                player->newdestY = board_to_screen(y - 1);
                return;
            }
            break;
        case DOWN:
            if (y < BOARD_HEIGHT - 1 && !board->cells[x + (y + 1) * board->width].is_wall)
            {
                player->newdir = DOWN;
                player->newdestX = board_to_screen(x);
                player->newdestY = board_to_screen(y + 1);
                return;
            }
            break;
        case LEFT:
            if (x > 0 && !board->cells[x - 1 + y * board->width].is_wall)
            {
                player->newdir = LEFT;
                player->newdestX = board_to_screen(x - 1);
                player->newdestY = board_to_screen(y);
                return;
            }
            break;
        case RIGHT:
            if (x < BOARD_WIDTH - 1 && !board->cells[x + 1 + y * board->width].is_wall)
            {
                player->newdir = RIGHT;
                player->newdestX = board_to_screen(x + 1);
                player->newdestY = board_to_screen(y);
                return;
            }
            break;
        default:
            break;
    }
}


void player_update_position(player_t* player, float velocity)
{
    switch(player->dir)
    {
        case UP:
            player->y -= velocity;
            player->x = player->destX;
            break;
        case DOWN:
            player->y += velocity;
            player->x = player->destX;
            break;
        case LEFT:
            player->x -= velocity;
            player->y = player->destY;
            break;
        case RIGHT:
            player->x += velocity;
            player->y = player->destY;
            break;
        default:
            break;
    }
}
