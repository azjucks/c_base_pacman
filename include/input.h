#ifndef __INPUT__
#define __INPUT__

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "defs.h"

typedef struct input_s
{
    E_DIR dir;


    bool enter;
    bool escape;
	bool debug;

    bool exit;
} input_t;

input_t* create_input();

void destroy_input(input_t* input);


void input_process(input_t* input);

void input_key_down(input_t* input, SDL_KeyboardEvent* event);
void input_key_up(input_t* input, SDL_KeyboardEvent* event);
void set_input(input_t* input, E_DIR dir);

#endif
