#include <stdio.h>

#include "types.h"
#include "utils.h"
#include "tokenizer.h"

void traverse_body(vector_statement res)
{
    for (int i = 0; i < res.size; i++)
    {
        if (res.s[0].type == INT_FUNCTION_DECLARATION)
        {
            d("Creating function: ");
            print_string(res.s[0].v.ifd.name);
            d("\nBody:\n");
            d("{");
            traverse_body(res.s[0].v.ifd.body);
            d("}");
        }
        else if (res.s[0].type == INT_DECLARATION)
        {
            d("\nCreating variable: ");
            print_string(res.s[0].v.vd.name);
            d("\nWith value: ");
            printf("%d", res.s[0].v.vd.value);
        }
        d("\n");
    }
}

void parse()
{
    vector_statement res = create_vector_statement(100, 0);
    vector_statement *current = &res;

    Token a;
    while (a.type != NONE)
    {
        a = next_token();
        if (a.type == CLPAR)
        {
            current = current->parent;
            continue;
        }
        if (a.type == INT)
        {
            a = next_token();
            if (a.type != ID)
            {
                err("Unexpected token after keyword int: ");
                print_string(a.value);
                return;
            }
            string name = a.value;
            a = next_token();
            if (a.type == E)
            {
                IntDeclaration id = (IntDeclaration){name, 0};
                add_statement_to_vector(current, (Statement){INT_DECLARATION, (StatementContainer)id});
                continue;
            }
            if (a.type == EQ)
            {
                a = next_token();
                IntDeclaration id = (IntDeclaration){name, stoi(a.value)};
                add_statement_to_vector(current, (Statement){INT_DECLARATION, (StatementContainer)id});
                // add expression with token value
                a = next_token();
                if (a.type != E)
                {
                    err("Expected ; but found: ");
                    print_string(a.value);
                    return;
                }
                continue;
            }
            if (a.type == OPBR)
            {
                a = next_token();
                // TODO: should support function arguments
                if (a.type != CLBR)
                {
                    err("Unexpected token: ");
                    print_string(a.value);
                    return;
                }
                a = next_token();
                if (a.type != OPPAR)
                {
                    err("Expected { but found: ");
                    print_string(a.value);
                    return;
                }
                vector_statement vs = create_vector_statement(100, current);
                IntFunctionDeclaration ifd = (IntFunctionDeclaration){name, vs};
                add_statement_to_vector(current, (Statement){INT_FUNCTION_DECLARATION, (StatementContainer)ifd});
                current = &current->s[current->size - 1].v.ifd.body;
                continue;
            }
            err("Unexpected token after identifier: ");
            print_string(a.value);
            printf("\n%d", a.type);
            return;
        }
        if (a.type == RET)
        {
            a = next_token();
            // TODO: Expression;
            a = next_token();
            if (a.type != E)
            {
                err("Expected ; but found: ");
                print_string(a.value);
                return;
            }
            continue;
        }
        if (a.type == NONE)
        {
            // TODO: return body
            traverse_body(res);
            return;
        }
    }
}