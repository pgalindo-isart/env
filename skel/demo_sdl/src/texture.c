
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>

#include "game_internal.h"

SDL_Texture* texture_load_transparent(SDL_Renderer* renderer, const char* file, u32 color_key)
{
    assert(renderer);
    assert(file);

    SDL_Surface* surface = SDL_LoadBMP(file);
    if (surface == NULL)
    {
        SDL_Log("Failed to open %s: %s", file, SDL_GetError());
        return NULL;
    }

    SDL_SetColorKey(surface, SDL_TRUE, color_key); 

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
        SDL_Log("Failed to create texture for %s: %s", file, SDL_GetError());

    SDL_FreeSurface(surface);

    return texture;
}

void texture_set_color_mod(SDL_Texture* texture, u32 color)
{
    Uint8 r = (0x00ff0000 & color) >> 16;
    Uint8 g = (0x0000ff00 & color) >> 8;
    Uint8 b = (0x000000ff & color) >> 0;
    SDL_SetTextureColorMod(texture, r, g, b);
}

