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
    EQ,
    EQCMP,
    GT,
    GET,
    LT,
    LET,
    RET,
    NONE
} TokenType;

typedef struct
{
    TokenType type;
    string value;
    //TokenDescription description;
} Token;

typedef union Statement Statement;

typedef struct vector_statement
{
    Statement *s;
    unsigned int size;
    unsigned int b_size;
} vector_statement;

typedef struct
{
    string name;
    vector_statement body;
} IntFunctionDeclaration;

typedef struct
{
    string name;
    int value;
} IntDeclaration;

union Statement {
    IntDeclaration vd;
    IntFunctionDeclaration ifd;
};

///////////////////////////////////////////////////////////////////////////
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

#endif