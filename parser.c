#include <stdio.h>

#include "types.h"
#include "utils.h"
#include "tokenizer.h"

void parse()
{
    Token a;

    while (a.type != NONE)
    {
        a = next_token();
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
                // Push in the queue
                d("Created an empty variable.\nName: ");
                print_string(name);
                continue;
            }
            if (a.type == EQ)
            {
                a = next_token();
                // add expression with token value
                d("Created variable. \nName: ");
                print_string(name);
                d("\nValue: ");
                print_string(a.value);
                d("\n");
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
            // TODO: Expression
            d("Returned value: ");
            print_string(a.value);
            continue;
        }
        //print_string(a.value);
        //printf("\n");
        //fflush(stdout);
        //a = next_token();
    }
}