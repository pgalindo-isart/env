
#include <SDL2/SDL_render.h>

#include "game_internal.h"

// Display monospaced font from a sprite-sheet, letters have to follow ascii order.
// Use CBFG to generate those textures.
void font_display(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, const char* ascii_text)
{
    assert(renderer);
    assert(texture);
    if (ascii_text == NULL)
        return;

    const int START_CHARACTER = 32;
    const int GLYPHS_PER_LINE = 32;
    const int GLYPH_WIDTH     = 8;
    const int GLYPH_HEIGHT    = 16;

    for (int i = 0; ascii_text[i] != '\0'; ++i)
    {
        unsigned char c = (unsigned char)ascii_text[i];

        int glyph_x = (c - START_CHARACTER) % GLYPHS_PER_LINE;
        int glyph_y = (c - START_CHARACTER) / GLYPHS_PER_LINE;
        SDL_Rect src = { glyph_x * GLYPH_WIDTH, glyph_y * GLYPH_HEIGHT, GLYPH_WIDTH, GLYPH_HEIGHT };
        SDL_Rect dst = { x + (i * GLYPH_WIDTH), y, GLYPH_WIDTH, GLYPH_HEIGHT };

        SDL_RenderCopy(renderer, texture, &src, &dst);
    }
}

