#include <stdio.h>

#include "types.h"
#include "file_reader.h"
#include "utils.h"
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"

void gen_asm(vector_statement res)
{
    for (int i = 0; i < res.size; i++)
    {
        if (res.s[i].type == INT_FUNCTION_DECLARATION)
        {
            d("Creating function: ");
            print_string(res.s[i].v.ifd.name);
            d("\nBody:\n");
            d("{");
            traverse_body(res.s[i].v.ifd.body);
            d("}");
        }
        else if (res.s[i].type == IF_ELSE_STATEMENT)
        {
            d("If statement expression: ");
            printf("%d", res.s[i].v.ies.expression);
            d("\nBody:\n");
            d("{");
            traverse_body(res.s[i].v.ies.body);
            d("}");
        }
        else if (res.s[i].type == INT_DECLARATION)
        {
            d("\nCreating variable: ");
            print_string(res.s[i].v.vd.name);
            d("\nWith value: ");
            printf("%d", res.s[i].v.vd.value);
        }
        else if (res.s[i].type == INT_VALUE_ASSIGMENT)
        {
            d("\nAssigning value to variable: ");
            print_string(res.s[i].v.vd.name);
            d("\nValue: ");
            printf("%d", res.s[i].v.vd.value);
        }
        else if (res.s[i].type == RETURN)
        {
            d("\nReturning: ");
            printf("%d", res.s[i].v.ret.value);
        }
        d("\n");
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Invalid number of arguments");
        return -1;
    }
    if (load_file(argv[1]) == 0)
    {
        printf("Cannot open the file or it is empty");
        return -2;
    }
    vector_statement program = create_vector_statement(100, 0);
    parse(&program);
    generate(program);
    d("\n");
    fflush(stdout);
}
