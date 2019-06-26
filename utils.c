void d(char *c)
{
    printf("%s", c);
}

void d(int *d)
{
    printf("%d", d);
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

char is_var_name_char(char *c)
{
    if (is_alpha(*c) || *c == '_')
        return 1;
    if (is_alpha(*c) || is_digit(*c) || *c == '_')
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