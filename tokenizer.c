#include <stdio.h>

#include "types.h"
#include "file_reader.h"
#include "utils.h"

#ifndef NULL
#define NULL 0
#endif

#define NEXT_CHAR(C) \
  C = next_char();   \
  if (C == NULL)     \
    return transform_to_token(buffer);

static int line = 0;
static char *c = NULL;

char *next_char()
{
  char *c = get_char(NULL);
  if (c == NULL)
    return NULL;
  if (*c == '\n')
    line++;
  return c;
}

Token transform_to_token(string s)
{
  if (s.size == 0)
    return (Token){NONE, (string){NULL, 0, 0}};
  if (str_cmp_char(s, "if"))
    return (Token){IF, s};
  if (str_cmp_char(s, "for"))
    return (Token){FOR, s};
  if (str_cmp_char(s, "int"))
    return (Token){INT, s};
  if (str_cmp_char(s, "return"))
    return (Token){RET, s};
  if (str_cmp_char(s, "<="))
    return (Token){LET, s};
  if (str_cmp_char(s, ">="))
    return (Token){GET, s};
  if (str_cmp_char(s, "=="))
    return (Token){EQCMP, s};
  if (is_digit(s.s))
    return (Token){CONST, s};
  if (is_valid_var_name(s.s))
    return (Token){ID, s};
  if (s.s[0] == ';')
    return (Token){E, s};
  if (s.s[0] == '(')
    return (Token){OPBR, s};
  if (s.s[0] == ')')
    return (Token){CLBR, s};
  if (s.s[0] == '{')
    return (Token){OPPAR, s};
  if (s.s[0] == '}')
    return (Token){CLPAR, s};
  if (s.s[0] == '=')
    return (Token){EQ, s};
  if (s.s[0] == '<')
    return (Token){LT, s};
  if (s.s[0] == '>')
    return (Token){GT, s};
  return (Token){NONE, s};
}

Token next_token()
{
  // TODO: Don't malloc every time
  string buffer = create_string(10);
  if (!c)
    NEXT_CHAR(c);
  while (is_whitespace(c))
  {
    NEXT_CHAR(c);
  }
  if (is_valid_var_name(c) == 1)
  {
    while (is_valid_var_name(c))
    {
      add_char_to_string(&buffer, *c);
      NEXT_CHAR(c);
    }
  }
  else if (is_digit(c))
  {
    while (is_digit(c))
    {
      add_char_to_string(&buffer, *c);
      NEXT_CHAR(c);
    }
  }
  else
  {
    add_char_to_string(&buffer, *c);
    NEXT_CHAR(c);
  }

  return transform_to_token(buffer);
}
