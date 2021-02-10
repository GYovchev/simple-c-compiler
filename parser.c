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

char expect(int expected)
{
    Token t = next_token();
    if (t.type != expected)
    {
        err("Expected token:");
        printf("%d", expected);
        d(" but found: ");
        print_string(t.value);
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

void parse(vector_statement* res)
{
    vector_statement *current = res;

    Token t;
    do {
        Token t = next_token();
        if (t.type == CLPAR)
        {
            if (current->parent == 0)
            {
                err("Unexpected }");
                return;
            }
            current = current->parent;
            continue;
        }
        else if (t.type == ID) {
            string name = t.value;
            t = next_token();
            if(t.type == EQ) {
                IntValueAssigment iva = (IntValueAssigment){name, read_expression()};
                add_statement_to_vector(current, (Statement){INT_VALUE_ASSIGMENT, (StatementContainer)iva});
                if (!expect(E))
                    return;
                continue;
            } else if(t.type == OPBR) {
                // TODO: Implement functions
            }
        }
        else if (t.type == INT)
        {
            t = next_token();
            if (t.type != ID)
            {
                err("Expected identifier but found: ");
                print_string(t.value);
                return;
            }
            string name = t.value;
            t = next_token();
            if (t.type == E)
            {
                IntDeclaration id = (IntDeclaration){name, 0};
                add_statement_to_vector(current, (Statement){INT_DECLARATION, (StatementContainer)id});
                continue;
            }
            if (t.type == EQ)
            {
                IntDeclaration id = (IntDeclaration){name, read_expression()};
                add_statement_to_vector(current, (Statement){INT_DECLARATION, (StatementContainer)id});
                if (!expect(E))
                    return;
                continue;
            }
            if (t.type == OPBR)
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
            print_string(t.value);
            printf("\n%d", t.type);
            return;
        }
        else if (t.type == RET)
        {
            add_statement_to_vector(current, (Statement){RETURN, (StatementContainer)(Return){read_expression()}});
            if (!expect(E))
                return;
            continue;
        }
        else if (t.type == IF)
        {
            if (!expect(OPBR))
                return;
            int exp = read_expression();
            if (!expect(CLBR))
                return;
            if (!expect(OPPAR))
                return;
            vector_statement vs = create_vector_statement(100, current);
            IfElseStatement ies = (IfElseStatement){exp, vs};
            add_statement_to_vector(current, (Statement){IF_ELSE_STATEMENT, (StatementContainer)ies});
            current = &current->s[current->size - 1].v.ies.body;
            continue;
        }
        else if (t.type == NONE)
        {
            // TODO: return AST
            traverse_body(*res);
            return;
        }
    } while (t.type != NONE);
}