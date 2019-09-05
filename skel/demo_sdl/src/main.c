
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <SDL2/SDL.h>

#include <game.h>

// Stuff needed by the SDL main loop
typedef struct context_t
{
    SDL_Window*       window;
    SDL_Renderer*     renderer;
    SDL_AudioDeviceID audio;
    SDL_AudioSpec     audio_spec;

    game_t* game;

    bool running;
    int frame_start_time;
} context_t;

bool context_init(context_t* context, int width, int height, int pixel_scale);
void context_destroy(context_t* context);
void context_start_frame(context_t* context, game_io_t* io);

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    // ====================================
    // Init game
    game_t* game  = game_create();
    game_io_t* io = game_get_io(game);

    // ====================================
    // Init SDL
    context_t context = {};
    if (context_init(&context, io->width_required, io->height_required, 2) == false)
        return 1;

    // ====================================
    // Load resources
    game_load_resources(game, context.renderer);

    // ====================================
    // Main loop
    context.game    = game;
    context.running = true;
    while (context.running)
    {
        // Start frame: (process events, update delta time)
        context_start_frame(&context, io);

        // Update game
        game_update(game);

        // Draw game
        game_display(game, context.renderer);

        // Present buffer
        SDL_RenderPresent(context.renderer);

        // Small delay to let the CPU breathe
        SDL_Delay(1);
    }

    game_destroy(game);
    context_destroy(&context);

    return 0;
}

void context_read_sound(context_t* context, float* buffer, int nb_samples, int nb_channels, int sampling_rate)
{
    memset(buffer, 0, nb_samples * nb_channels * sizeof(float));
    if (context->game == NULL)
        return;

    game_sound_get_samples(context->game, buffer, nb_samples, nb_channels, sampling_rate);
}

void sdl_audio_callback(void* userdata, Uint8* buffer_raw, int len)
{
    context_t* context = userdata;
    SDL_AudioSpec* spec = &context->audio_spec;

    // Sound buffer boundaries
    float* buffer        = (float*)buffer_raw;
    float* buffer_end    = (float*)&buffer_raw[len];
    int nb_samples_total = buffer_end - buffer;

    // Get nb samples from buffer info
    assert(nb_samples_total % spec->channels == 0);
    int nb_samples = nb_samples_total / spec->channels;

    context_read_sound(context, buffer, nb_samples, spec->channels, spec->freq);
}

bool context_init(context_t* context, int width, int height, int pixel_scale)
{
    assert(context != NULL);
    atexit(SDL_Quit); // Tell the program to call SDL_Quit() when it exits

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return false;
    }

    // Create SDL window
    context->window = SDL_CreateWindow("Breakout",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width * pixel_scale, height * pixel_scale,
            SDL_WINDOW_SHOWN);
    if (context->window == NULL)
    {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        return false;
    }

    // Create SDL renderer
    context->renderer = SDL_CreateRenderer(context->window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (context->renderer == NULL)
    {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        return false;
    }
    SDL_RenderSetScale(context->renderer, pixel_scale, pixel_scale);

    // Create SDL audio device
    {
        SDL_AudioSpec desired = {};
        desired.freq     = 48000;
        desired.format   = AUDIO_F32;
        desired.channels = 2;
        desired.samples  = 4096;
        desired.callback = sdl_audio_callback;
        desired.userdata = context;

        SDL_AudioSpec obtained = {};
        context->audio = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained,
                SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
        context->audio_spec = obtained;

        if (context->audio == 0)
        {
            SDL_Log("SDL_OpenAudioDevice error: %s", SDL_GetError());
        }
        else
        {
            // Start audio engine (will consume callback)
            SDL_PauseAudioDevice(context->audio, 0);
        }
    }

    return true;
}

void context_destroy(context_t* context)
{
    assert(context != NULL);

    SDL_DestroyRenderer(context->renderer);
    context->renderer = NULL;

    SDL_DestroyWindow(context->window);
    context->window = NULL;

    SDL_CloseAudioDevice(context->audio);
    context->audio = 0;
}

typedef struct key_mapping_t
{
    int game_key;
    int sdl_key;
} key_mapping_t;

void context_start_frame(context_t* context, game_io_t* io)
{
    assert(context != NULL);
    assert(io != NULL);

    // ====================================
    // Compute delta time
    unsigned int current_time = SDL_GetTicks();
    unsigned int previous_time = context->frame_start_time;

    if (previous_time > 0)
        io->delta_time = (current_time - previous_time) / 1000.f;
    else
        io->delta_time = 1.f / 60.f;

    context->frame_start_time = current_time;

    // ====================================
    // Handle events: update game input
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // Triggered when user close the app
            case SDL_QUIT:
                context->running = false;
                break;

            // Triggered on keyboard key down
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    context->running = false;
                break;

            default:
                break;
        }
    }

    // Input mapping
    const key_mapping_t keymap[] = {
        { GAME_KEY_LEFT,  SDL_SCANCODE_LEFT  },
        { GAME_KEY_RIGHT, SDL_SCANCODE_RIGHT },
        { GAME_KEY_UP,    SDL_SCANCODE_UP    },
        { GAME_KEY_DOWN,  SDL_SCANCODE_DOWN  },
        { GAME_KEY_SPACE, SDL_SCANCODE_SPACE },
        { -1,             -1                 }
    };

    const Uint8* sdl_keys = SDL_GetKeyboardState(NULL);
    for (const key_mapping_t* map = &keymap[0]; map->sdl_key != -1; ++map)
        io->keys[map->game_key] = sdl_keys[map->sdl_key];
}

size_t platform_load_file_into_buffer(char** buffer, const char* filename)
{
    assert(buffer != NULL);

    SDL_RWops* file = SDL_RWFromFile(filename, "r");
    file->seek(file, 0, RW_SEEK_END);
    size_t file_size = SDL_RWtell(file);
    file->seek(file, 0, SEEK_SET);
    // Alloc file_size + 1 so the last word will be null-terminated
    *buffer = calloc(file_size+1, sizeof(char));
    file->read(file, *buffer, 1, file_size);
    file->close(file);

    return file_size;
}
