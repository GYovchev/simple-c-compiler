#include <stdio.h>

#include "types.h"
#include "utils.h"
#include "tokenizer.h"

void traverse_body(vector_statement res)
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
        else if (res.s[i].type == RETURN)
        {
            d("\nReturning: ");
            printf("%d", res.s[i].v.ret.value);
        }
        d("\n");
    }
}

char expect(int expected)
{
    Token a = next_token();
    if (a.type != expected)
    {
        err("Expected token:");
        printf("%d", expected);
        d(" but found: ");
        print_string(a.value);
        return 0;
    }
    return 1;
}

// TODO: Should parse rel expression
int read_expression()
{
    Token t = next_token();
    return stoi(t.value);
}

void parse()
{
    vector_statement res = create_vector_statement(100, 0);
    vector_statement *current = &res;

    // char inside_one_line_body = 0;

    Token a;
    while (a.type != NONE)
    {
        a = next_token();
        // if (inside_one_line_body > 0)
        // {
        //     inside_one_line_body--;
        //     if (inside_one_line_body == 0)
        //     {
        //         current = current->parent;
        //     }
        // }
        if (a.type == CLPAR)
        {
            if (current->parent == 0)
            {
                err("Unexpected }");
                return;
            }
            current = current->parent;
            continue;
        }
        if (a.type == INT)
        {
            a = next_token();
            if (a.type != ID)
            {
                err("Expected identifier but found: ");
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
                IntDeclaration id = (IntDeclaration){name, read_expression()};
                add_statement_to_vector(current, (Statement){INT_DECLARATION, (StatementContainer)id});
                if (!expect(E))
                    return;
                continue;
            }
            if (a.type == OPBR)
            {
                // TODO: should support function arguments
                if (!expect(CLBR))
                    return;
                if (!expect(OPPAR))
                    return;
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
            add_statement_to_vector(current, (Statement){RETURN, (StatementContainer)(Return){read_expression()}});
            if (!expect(E))
                return;
            continue;
        }
        if (a.type == IF)
        {
            if (!expect(OPBR))
                return;
            int exp = read_expression();
            if (!expect(CLBR))
                return;
            // inside_one_line_body = 2;
            // TODO: Should support one line bodies
            if (!expect(OPPAR))
                return;
            vector_statement vs = create_vector_statement(100, current);
            IfElseStatement ies = (IfElseStatement){exp, vs};
            add_statement_to_vector(current, (Statement){IF_ELSE_STATEMENT, (StatementContainer)ies});
            current = &current->s[current->size - 1].v.ies.body;
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