#ifndef __DEFS__
#define __DEFS__

// 28 tiles width 896
// 31 tiles height 1088

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1200


#define BOARD_WIDTH 32
#define BOARD_HEIGHT 35

#define UNIT_SIZE 32

#define OFFSET 32

#define PLAYER_START_X 16
#define PLAYER_START_Y 19
#define PLAYER_SPEED 200

#define MAX_ENEMIES 4


typedef enum
{
    RIGHT,
    DOWN,
    LEFT,
    UP,

    NONE
}E_DIR;

typedef struct vector2_s
{
    int x;
    int y;
} vector2_t;

#endif
