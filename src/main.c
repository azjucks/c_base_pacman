#include "game.h"

int main(int argc, char* argv[])
{
    game_t* game = create_game();
    
    game_main_loop(game);

    return 0;
}
