#include <stdio.h>

#include "file_reader.h"

#define READ_FILE_BUF_SIZE 15

static char *last_char = NULL;
static FILE *source_file = NULL;
static char buffer[READ_FILE_BUF_SIZE];
static size_t buffer_size = 0;

/**
 * Reads next character from file. It is faster than `getc`.
 * returns NULL - if the file does not exist or next character is EOF or 
 * char* - pointer to the next char in the file
 */
char *next_char(char *name)
{
    char lf = load_file(name);
    if (lf == 0 && name != NULL)
        return NULL;
    if (last_char == NULL || last_char == buffer + buffer_size)
    {
        if (source_file != NULL)
        {
            buffer_size = fread(buffer, 1, READ_FILE_BUF_SIZE - 1, source_file);
            last_char = buffer;
            if (feof(source_file))
            {
                fclose(source_file);
                source_file = NULL;
            }
        }
        else
        {
            // We have no file to read from and no char to return
            return NULL;
        }
    }
    return last_char++;
}

char load_file(char *name)
{
    if (name != NULL)
    {
        if (source_file != NULL)
        {
            fclose(source_file);
            last_char = NULL;
        }
        source_file = fopen(name, "r");
        if (source_file == NULL)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}