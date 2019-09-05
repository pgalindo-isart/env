
#include "game_internal.h"

char* str_advance_to(char* cursor, const char* end, char c)
{
    while (cursor < end && *cursor != c)
        cursor++;
    return cursor;
}

