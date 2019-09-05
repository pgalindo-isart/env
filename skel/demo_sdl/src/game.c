
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include <SDL2/SDL_render.h>

#include "game_internal.h"
#include "breakout_internal.h"
#include "localization.h"

game_t* game_create()
{
    game_t* game = calloc(1, sizeof(game_t));
    game->loc    = calloc(1, sizeof(localization_t));

    // Display
    game->io.width_required   = WIDTH;
    game->io.height_required  = HEIGHT;

    // Sound
    game->io.mute   = true;
    game->io.volume = 0.3f;

    game->update_accum = 1.f / UPDATE_FRAMERATE;

    // Logic
    game->logic = breakout_create();

    return game;
}

void game_destroy(game_t* game)
{
    assert(game);

    game_unload_resources(game);
    breakout_destroy(game->logic);
    free(game->loc);
    free(game);
}

void game_load_resources(game_t* game, SDL_Renderer* renderer)
{
    assert(game);
    assert(renderer);

    // Load font
    game->font_texture = texture_load_transparent(renderer, "assets/font.bmp", 0x00000000);

    // Load loc
    localization_load(game->loc, "assets/loc_fr.txt");
}

void game_unload_resources(game_t* game)
{
    assert(game);

    SDL_DestroyTexture(game->font_texture);
    game->font_texture = NULL;

    localization_unload(game->loc);
}

game_io_t* game_get_io(game_t* game)
{
    assert(game);

    return &game->io;
}

void game_tick(game_t* game)
{
    assert(game);

    game_io_t* io = &game->io;
    if (io->keys[GAME_KEY_LEFT])
        printf("LEFT\n");
    if (io->keys[GAME_KEY_RIGHT])
        printf("RIGHT\n");
    if (io->keys[GAME_KEY_UP] && !game->previous_keys[GAME_KEY_UP])
        printf("UP\n");
    fflush(stdout);

    breakout_tick(game->logic);
}

void game_update(game_t* game)
{
    assert(game);

    game_io_t* io = &game->io;
    game->update_accum += io->delta_time;

    // Fixed frametime update
    float frame_time = 1.f / UPDATE_FRAMERATE;
    while (game->update_accum > frame_time)
    {
        game_tick(game);
        game->update_accum -= frame_time;
    }

    // Store key state
    memcpy(game->previous_keys, io->keys, GAME_KEY_COUNT * sizeof(bool));
}

void game_sound_get_samples(game_t* game, float* buffer, int nb_samples,
        int nb_channels, int sampling_rate)
{
    if (game->io.mute || game->io.volume <= 0.f)
        return;

    const float freq   = 440.f;
    const float volume = game->io.volume;
    static float phase = 0.f;

    for (int i = 0; i < nb_samples; ++i)
    {
        float sample = sin(phase * 2.f * M_PI);
        phase += freq / sampling_rate;
        phase = fmod(phase, 1.f);

        sample *= volume;

        for (int c = 0; c < nb_channels; ++c)
            buffer[i * nb_channels + c] += sample;
    }
}

void game_display(game_t* game, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x33, 0x66, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    int line_height = 14;
    int pen_x = 0;
    int pen_y = 0;

    u32 color = 0x00ffffff;

    texture_set_color_mod(game->font_texture, color);

    font_display(renderer, game->font_texture, pen_x, pen_y += line_height, game->loc->hello);
    font_display(renderer, game->font_texture, pen_x, pen_y += line_height, game->loc->test1);
    font_display(renderer, game->font_texture, pen_x, pen_y += line_height, game->loc->score);
}

