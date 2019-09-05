
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL_rwops.h>

#include "game_internal.h"

#include "localization.h"

void localization_load(localization_t* loc, const char* filename)
{
    assert(loc != NULL);
    assert(loc->buffer == NULL);

    // Load file into loc->buffer
    size_t filesize = platform_load_file_into_buffer(&loc->buffer, filename);

    const char SEPARATOR  = '\t';
    const char TERMINATOR = '\n';

    // Parse loc file
    char* cursor = loc->buffer;
    const char* end = &loc->buffer[filesize];
    while (cursor < end)
    {
        char* key_start = cursor;
        cursor = str_advance_to(cursor, end, SEPARATOR);
        if (cursor == end) break;

        int key_len = cursor - key_start;
        cursor++;

        char* word_start = cursor;
        cursor = str_advance_to(cursor, end, TERMINATOR);
        *cursor = '\0'; // Replace \n by \0 so each word is null-terminated

        // Some macro-fu
        // Will generate "else if (strcmp(...)) ..." for each loc_key
        if (0);
#define LOC_MACRO(loc_key) else if (strncmp(key_start, #loc_key, key_len) == 0) loc->loc_key = word_start;
#include "loc.inc"
#undef LOC_MACRO

        cursor++;
    }
}

void localization_unload(localization_t* loc)
{
    free(loc->buffer);
    memset(loc, 0, sizeof(localization_t));
}

