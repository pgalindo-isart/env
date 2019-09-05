#pragma once

#include "game_internal.h"

static const int BRICK_WIDTH  = 16;
static const int BRICK_HEIGHT = 8;
static const int BRICK_SPACE  = 4;
static const int PLAYER_Y     = 10;

enum brick_state
{
    BS_ALIVE,
    BS_DESTROYED
};

typedef struct brick_t
{
    int x;
    int y;
    int state;
} brick_t;

typedef struct breakout_logic_t
{
    int lives;
    int player_pos_x;
    int player_size;

    int brick_count;
    brick_t* bricks;

    v2 ball_pos;
    v2 ball_vel;
} breakout_logic_t;

breakout_logic_t* breakout_create(void);
void breakout_destroy(breakout_logic_t* breakout);
void breakout_tick(breakout_logic_t* breakout);