#pragma once

#include <assert.h>

#include <game.h>

typedef struct SDL_Texture SDL_Texture;

static const int WIDTH  = 400;
static const int HEIGHT = 300;
static const int UPDATE_FRAMERATE = 60; // 60Hz game

typedef struct localization_t localization_t;
typedef struct breakout_logic_t breakout_logic_t;

typedef struct game_t
{
    // We use a fixed framerate
    float update_accum;

    // State of keys at the last update
    // Used to check if key is just pressed/released
    bool previous_keys[GAME_KEY_COUNT];

    // Sprite-sheet for font display
    SDL_Texture* font_texture;

    // Store localization buffer
    localization_t* loc;

    breakout_logic_t* logic;

    // Input/Ouput
    game_io_t io;
} game_t;

// Utils
char* str_advance_to(char* cursor, const char* end, char c);

// Localization
void localization_load(localization_t* loc, const char* filename);
void localization_unload(localization_t* loc);

// Texture
void texture_set_color_mod(SDL_Texture* texture, u32 color);
SDL_Texture* texture_load_transparent(SDL_Renderer* renderer, const char* file, u32 color_key);

// Font
void font_display(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, const char* ascii_text);

