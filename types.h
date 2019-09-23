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

typedef struct Statement Statement;

typedef struct vector_statement
{
    Statement *s;
    unsigned int size;
    unsigned int b_size;
    void *parent;
} vector_statement;

typedef struct Variable
{
    string name;
    char type; // 0-local; 1-dynamic
    char data_type; // 0-int
    int place;
} Variable;

typedef struct variable_map
{
    Variable *v;
    unsigned int size;
    unsigned int b_size;
} variable_map;

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

typedef struct
{
    string name;
    int value;
} IntValueAssigment;

typedef struct
{
    int value;
} Return;

typedef struct
{
    int expression;
    vector_statement body;
} IfElseStatement;

typedef union {
    IntDeclaration vd;
    IntFunctionDeclaration ifd;
    Return ret;
    IfElseStatement ies;
    IntValueAssigment iva;

} StatementContainer;

typedef enum
{
    INT_DECLARATION,
    INT_VALUE_ASSIGMENT,
    INT_FUNCTION_DECLARATION,
    RETURN,
    IF_ELSE_STATEMENT
} StatementType;

struct Statement
{
    StatementType type;
    StatementContainer v;
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