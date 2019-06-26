typedef enum TokenType
{
    VAR_INIT
} TokenType;

typedef enum DataType
{
    INT,
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
    TokenDescription description;
} Token;