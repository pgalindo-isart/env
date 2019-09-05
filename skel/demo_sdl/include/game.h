#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t u32;

typedef struct v2
{
    float x;
    float y;
} v2;

typedef struct v4
{
    float r;
    float g;
    float b;
    float a;
} v4;

enum game_keys
{
    GAME_KEY_LEFT = 1,
    GAME_KEY_RIGHT,
    GAME_KEY_UP,
    GAME_KEY_DOWN,
    GAME_KEY_SPACE,

    GAME_KEY_DEBUG1,
    GAME_KEY_DEBUG2,
    GAME_KEY_DEBUG3,
    GAME_KEY_DEBUG4,

    GAME_KEY_COUNT
};

// Communication between app (the system) and game
typedef struct game_io_t
{
    // INPUT: Set by the app
    float delta_time;

    bool keys[GAME_KEY_COUNT];

    bool mute;
    float volume;

    // OUTPUT: For read only, set by game
    int width_required;
    int height_required;
    int update_framerate;

} game_io_t;

// Forward declarations
typedef struct game_t game_t;
typedef struct SDL_Renderer SDL_Renderer;

// =================================================================================
// Platform specific functions
size_t platform_load_file_into_buffer(char** buffer, const char* filename);
// TODO: alloc/free memory, log

// =================================================================================
// Game functions

// CREATION/DESTRUCTION
game_t* game_create();
void game_destroy(game_t* game);
void game_load_resources(game_t* game, SDL_Renderer* renderer);
void game_unload_resources(game_t* game);

// INPUT/OUTPUT
game_io_t* game_get_io(game_t* game);

// LOGIC
void game_update(game_t* game);

// AUDIO
void game_sound_get_samples(game_t* game, float* buffer, int nb_samples,
        int nb_channels, int sampling_rate);

// DISPLAY
void game_display(game_t* game, SDL_Renderer* renderer);
