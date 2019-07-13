#ifndef TYPES_H_
#define TYPES_H_

typedef struct string
{
    char *s;
    unsigned int size;
    unsigned int b_size;
} string;

typedef enum TokenType
{
    ID,
    INT,
    IF,
    FOR,
    CONST,
    OPBR,
    CLBR,
    OPPAR,
    CLPAR,
    E,
    NONE
} TokenType;

typedef enum DataType
{
    //INT,
    CHAR
} DataType;

typedef struct
{
    char *name;
    int name_len;
    DataType type;
} VarDeclarationToken;

typedef struct
{
    char *name;
    int name_len;
    DataType type;
    union {
        char char_value;
        int int_value;
    } value;
} VarAssingmentToken;

typedef union {
    VarDeclarationToken var_init;
    VarAssingmentToken var_assignment;
} TokenDescription;

typedef struct
{
    TokenType type;
    string value;
    //TokenDescription description;
} Token;

#endif