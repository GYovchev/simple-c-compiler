#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "types.h"

void d(char *c)
{
  printf("%s", c);
}

void err(char *c)
{
  d("ERROR: ");
  d(c);
}

char is_alpha(char *c)
{
  if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
    return 1;
  return 0;
}

char is_digit(char *c)
{
  if (*c >= '0' && *c <= '9')
    return 1;
  return 0;
}

char is_whitespace(char *c)
{
  if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r')
    return 1;
  return 0;
}

char is_var_name_char(char *c)
{
  if (is_alpha(c) || *c == '_')
    return 1;
  if (is_alpha(c) || is_digit(c) || *c == '_')
    return 2;
  return 0;
}

char is_valid_var_name(char *c)
{
  if (is_var_name_char(c) != 1)
    return 0;
  for (char *i = c + 1; *i != 0; i++)
  {
    if (!is_valid_var_name)
      return 0;
  }
  return 1;
}

char str_equal(char *a, char *b)
{
  int i;
  for (i = 0; a[i] != 0 && b[i] != 0; i++)
  {
    if (a[i] != b[i])
      return 0;
  }
  if (a[i] != b[i])
    return 0;
  return 1;
}

char is_keyword(char *c)
{
  if (str_equal(c, "int"))
  {
    return 1;
  }
  if (str_equal(c, "char"))
  {
    return 2;
  }

  return 0;
}

string create_string(size_t size)
{
  if (size < 16)
    size = 16;
  return (string){malloc(size), 0, size};
}

void add_char_to_string(string *s, char c)
{
  if (s != NULL)
  {
    if (s->b_size == s->size)
    {
      s = realloc(s, s->b_size * 2);
    }
    s->s[s->size] = c;
    s->size++;
  }
}

vector_statement create_vector_statement(size_t size, vector_statement *parent)
{
  if (size < 16)
    size = 16;
  return (vector_statement){malloc(size * sizeof(Statement)), 0, size, parent};
}

void add_statement_to_vector(vector_statement *vs, Statement s)
{
  if (vs != NULL)
  {
    if (vs->b_size == vs->size)
    {
      vs = realloc(vs, vs->b_size * sizeof(Statement) * 2);
    }
    vs->s[vs->size] = s;
    vs->size++;
  }
}

void print_string(string s)
{
  for (size_t i = 0; i < s.size; i++)
  {
    printf("%c", s.s[i]);
  }
}

char str_cmp_str(string a, string b)
{
  if (a.size != b.size)
    return 0;
  for (size_t i = 0; i < a.size; i++)
  {
    if (a.s[i] != b.s[i])
      return 0;
  }
  return 1;
}

char str_cmp_char(string a, char *b)
{
  size_t i;
  for (i = 0; i < a.size; i++)
  {
    if (b[i] == 0 || a.s[i] != b[i])
      return 0;
  }
  if (b[i])
    return 0;
  return 1;
}

int stoi(string n)
{
  int res = 0;
  int power = 1;
  for (char *i = n.s + n.size - 1; i >= n.s; i--)
  {
    res += power * (*i - '0');
    power *= 10;
  }
  return res;
}