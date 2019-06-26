#include "tokens.h"
#include "file_reader.h"
#include "utils.h"

#define NULL 0

static int line = 0;

Token *next_token()
{
    char *c = next_char(NULL);
    if (is_valid_var_name(c) == 1)
    {
        while (1)
        {
            char *c = next_char(NULL);
            if (c == NULL)
                return;
            printf("%c", *c);
        }
    }
    else if (is_digit(c))
    {
    }
    printf("Error on line %d", d);
    return NULL;
}