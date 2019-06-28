#include <stdio.h>

#include "tokens.h"
#include "file_reader.h"
#include "utils.h"

#ifndef NULL
#define NULL 0
#endif

#define NEXT_CHAR(C) \
  C = next_char();   \
  if (C == NULL)     \
    return NULL;

static int line = 0;

char *next_char()
{
  char *c = get_char(NULL);
  if (*c == '\n')
    line++;
  return c;
}

Token *next_token()
{
  char *c = next_char();
  if (is_valid_var_name(c) == 1)
  {
    while (is_valid_var_name(c))
    {
      printf("%c", *c);
      NEXT_CHAR(c)
      if (is_whitespace(c))
      {
        while (is_whitespace(c))
        {
          printf("%c", *c);
          NEXT_CHAR(c)
        }

        if (is_valid_var_name(c) == 1)
        {
          while (is_valid_var_name(c))
          {
            printf("%c", *c);
            NEXT_CHAR(c)
          }
        }
      }
    }
  }
  else if (is_digit(c))
  {
  }
  printf("\nError on line %d\n", line);
  return NULL;
}
