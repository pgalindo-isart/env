#pragma once

typedef struct localization_t
{
    char* buffer;
    // This preprocessor will generate a "const char*" member for each 
    // lock_key in loc.in
#define LOC_MACRO(loc_key) const char* loc_key;
#include "loc.inc"
#undef LOC_MACRO
} localization_t;

