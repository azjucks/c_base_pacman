#include "game.h"

game_t* create_game()
{
    game_t* game = malloc(sizeof(game_t));
    
    game->draw = create_draw(game);
    game->board = create_board(game);
    game->input = create_input();
    game->player = create_player(game);

    game->enemies = create_enemy_list();

    game->current_score = 0;
    game->high_score = 0;
	
    

	return game;
}

void reset_game(game_t* game)
{
    game->current_score = 0;
    
    // destroy_enemy_list(game->enemies);
    
}

void destroy_game(game_t* game)
{
    free(game->draw);
    free(game->input);
    destroy_player(game->player);
    
    // destroy_enemy_list(game->enemies);

    free(game);
}


void game_main_loop(game_t* game)
{
	Uint64 frequency = SDL_GetPerformanceFrequency();
	Uint64 counter = 0;
    float delta = 0.f;


	SDL_SetRenderDrawColor(game->draw->renderer, 29, 36, 54, 255);

    bool running = true;
    
    while (running)
    {
		
        input_process(game->input);

		Uint64 current_counter = SDL_GetPerformanceCounter();
		delta = counter > 0 ? (current_counter - counter) / (float)frequency : 1.f / 60.f;
		counter = current_counter;
		
        // QUIT GAME INSTANTLY
        if (game->input->exit)
            break;
        
        // PAUSE GAME
        if (game->input->escape)
        {
            game->input->escape = false;
            while (game->input->escape == false)
            {
                input_process(game->input);
                // PAUSE
            }
            game->input->escape = false;
        }

		SDL_SetRenderDrawColor(game->draw->renderer, 29, 36, 54, 255);
		SDL_RenderClear(game->draw->renderer);
		
        Uint32 ticks = SDL_GetTicks();

        Uint32 item_render_frequency = ticks / 200;

        Uint32 player_render_frequency = ticks / 200;

		draw_board(game, item_render_frequency);
		draw_player(game, player_render_frequency);
		
		if (game->input->debug)
		{
			draw_debug(game);
		}
		// Move player
		
        player_process(game, delta);

		SDL_RenderPresent(game->draw->renderer);

        // Restart delta timer
        delta = 0.f;
    }
}
