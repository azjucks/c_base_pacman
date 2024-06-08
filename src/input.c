#include "input.h"

#include <stdlib.h>


input_t* create_input()
{
    input_t* input = malloc(sizeof(input_t));
    input->dir = NONE;

    input->enter = 0;
    input->escape = 0;
	input->debug = 0;

    input->exit = 0;

    return input;
}

void destroy_input(input_t* input)
{
    free(input);
}

void input_process(input_t* input)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                input->exit = 1;
                break;
            case SDL_KEYDOWN:
                input_key_down(input, &event.key);
                break;
            case SDL_KEYUP:
                //input_key_up(input, &event.key);
                break;
            default:
                break;
        }
    }
}

void input_key_down(input_t* input, SDL_KeyboardEvent* event)
{
    switch(event->keysym.scancode)
    {
        case SDL_SCANCODE_RETURN:
            input->enter = 1;
            break;
        case SDL_SCANCODE_ESCAPE:
            input->escape = 1;
            break;
		case SDL_SCANCODE_F5:
			input->debug = !input->debug;
			break;
        case SDL_SCANCODE_UP:
            input->dir = UP;
            break;
        case SDL_SCANCODE_DOWN:
            input->dir = DOWN;
            break;
        case SDL_SCANCODE_LEFT:
            input->dir = LEFT;
            break;
        case SDL_SCANCODE_RIGHT:
            input->dir = RIGHT;
            break;
        default:
            break;
    }
}

void input_key_up(input_t* input, SDL_KeyboardEvent* event)
{
    switch(event->keysym.scancode)
    {
        case SDL_SCANCODE_UP:
            input->dir = NONE;
            break;
        case SDL_SCANCODE_DOWN:
            input->dir = NONE;
            break;
        case SDL_SCANCODE_LEFT:
            input->dir = NONE;
            break;
        case SDL_SCANCODE_RIGHT:
            input->dir = NONE;
            break;
        default:
            break;
    }
}
