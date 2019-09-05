
#include <stdlib.h>

#include "breakout_internal.h"

breakout_logic_t* breakout_create(void)
{
    breakout_logic_t* breakout = calloc(1, sizeof(breakout_logic_t));

    int bricks_row = 8;
    int bricks_col = WIDTH / (BRICK_WIDTH + BRICK_SPACE);

    breakout->bricks = calloc(bricks_row * bricks_col, sizeof(brick_t));

    // Place bricks
    for (int y = 0; y < bricks_row; ++y)
    {
        for (int x = 0; x < bricks_col; ++x)
        {
            brick_t* brick = &breakout->bricks[x + y * bricks_col];

            brick->x = x;
            brick->y = y;
            brick->state = BS_ALIVE;
        }
    }

    // Place player at center
    breakout->player_size = 32;
    breakout->player_pos_x = (WIDTH + breakout->player_size) / 2;

    // Place ball
    breakout->ball_pos.x = breakout->player_pos_x;
    breakout->ball_pos.y = PLAYER_Y + 5;
    breakout->ball_vel.x = 1.f;
    breakout->ball_vel.y = 0.5f;

    breakout->lives = 3;

    return breakout;
}

void breakout_destroy(breakout_logic_t* breakout)
{
    free(breakout->bricks);
    free(breakout);
}

void breakout_tick(breakout_logic_t* breakout)
{
    v2 pos = breakout->ball_pos;
    if (pos.y < 0)
        return;

    pos.x += breakout->ball_vel.x;
    pos.y += breakout->ball_vel.y;

    // Check collision and change direction

    // Wall
    if (pos.x > WIDTH || pos.x < 0)
        breakout->ball_vel.x *= -1;
    if (pos.y > HEIGHT)
        breakout->ball_vel.y *= -1;

    if (pos.y < 0)
    {
        // Lost
    }

    breakout->ball_pos = pos;
}

