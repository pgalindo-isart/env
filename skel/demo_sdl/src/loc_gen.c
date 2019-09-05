
#include <stdlib.h>
#include <stdio.h>

void print_inc(char* infile)
{
    char* buffer;
    size_t buffer_size;
    {
        FILE* file = fopen(infile, "r");
        fseek(file, 0, SEEK_END);
        buffer_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = calloc(buffer_size, sizeof(char));
        fread(buffer, 1, buffer_size, file);
        fclose(file);
    }

    char* cursor = buffer;
    const char* end = &buffer[buffer_size];
    while (cursor < end)
    {
        char* key_start = cursor;
        while (cursor < end && *cursor != '\t')
            cursor++;
        if (cursor >= end) break;

        int key_len = cursor - key_start;
        cursor++;
        if (cursor >= end) break;

        printf("LOC_MACRO(%.*s)\n", key_len, key_start);

        while (cursor < end && *cursor != '\n')
            cursor++;
        if (cursor >= end) break;

        cursor++;
    }

    free(buffer);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s LOC_FILE1 [LOC_FILE2 ...]\n", argv[0]);
        return 1;
    }

    argv++;

    while (*argv)
    {
        print_inc(*argv);
        argv++;
    }

    return 0;
}

