void d(char *c);

char is_alpha(char *c);
char is_digit(char *c);
char is_whitespace(char *c);

/**
 * Is that symbol permited for use in a variable name
 * Returns:
 * 0 - cant be used
 * 1 - can be used as first char
 * 2 - can be used
 */
char is_var_name_char(char *c);
char is_valid_var_name(char *c);

char str_equal(char *a, char *b);

/**
 * Checks if string is keyword and returns it's type
 * 0 - no
 * 1 - int
 * 2 - char
 */
char is_keyword(char *c);

typedef struct string string;
struct string
{
    char *s;
    unsigned int size;
    unsigned int b_size;
};

string create_string(size_t size);

void add_char_to_string(string *s, char c);

void print_string(string s);

char str_cmp_str(string a, string b);
char str_cmp_char(string a, char *b);