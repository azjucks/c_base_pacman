#include "board.h"

unsigned int matrix_filter(board_t* board, int x, int y)
{
    unsigned int res = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
                continue;

            if ((x + j < 0 && x + j >= board->width - 1 && y + i < 0 && y + i >= board->height)
                || board->cells[x + j + (y + i) * board->width].is_wall)
            {
                res += 1;
            }
            res <<= 1;
        }
    }
    res >>= 1;

    return res;
}

E_CELL_SPRITE get_cell_sprite(board_t* board, int x, int y)
{
    int r = matrix_filter(board, x, y);
    switch(r)
    {
        case 31:
            return E_U;
        case 159:
            return E_U;
        case 63:
            return E_U; 

        case 248:
            return E_D;
        case 252:
            return E_D;
        case 249:
            return E_D;

        case 214:
            return E_L;
        case 215:
            return E_L;
        case 246:
            return E_L;
        case 247:
            return E_L;

        case 107:
            return E_R;
        case 111:
            return E_R;
        case 235:
            return E_R;
        case 239:
            return E_R;
        
        case 223:
            return E_C_U_R;
        case 127 :
            return E_C_U_L;
        case 251:
            return E_C_D_L;
        case 254 :
            return E_C_D_R;

        case 11:
            return E_D_R;
        case 22:
            return E_D_L;
        case 208:
            return E_U_L;
        case 105:
            return E_U_R;
        case 104:
            return E_U_R;
        case 212:
            return E_U_L;

        default:
            return E_DEFAULT;

    }
}

void set_tile_cell_sprite(board_t* board)
{
    for (int j = 0; j < board->height; ++j)
    {
        for (int i = 0; i < board->width; ++i)
        {
            tile_t tile;
            tile.width = UNIT_SIZE;
            tile.height = UNIT_SIZE;
            E_CELL_SPRITE index = get_cell_sprite(board, i, j);
            board->cells[i + j * board->width].index = index;
            tile.row = index / 4;
            tile.column = index % 4;
            board->cells[i + j * board->width].tile = tile;
        }
    }
}
