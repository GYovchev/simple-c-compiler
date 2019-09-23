#include <stdio.h>

#include "types.h"
#include "utils.h"

void generate(vector_statement res)
{
    variable_map vm = create_variable_map();
    int place = 4;
    for (int i = 0; i < res.size; i++)
    {
        if (res.s[i].type == INT_FUNCTION_DECLARATION)
        {
            d(".globl ");print_string(res.s[i].v.ifd.name);
            d("\n");print_string(res.s[i].v.ifd.name);d(":\n");
            d("pushq	%rbp\n");
            d("movq	%rsp, %rbp\n");
            generate(res.s[i].v.ifd.body);
        }
        else if (res.s[i].type == IF_ELSE_STATEMENT)
        {
            d("If statement expression: ");
            printf("%d", res.s[i].v.ies.expression);
            d("\nBody:\n");
            d("{");
            generate(res.s[i].v.ies.body);
            d("}");
        }
        else if (res.s[i].type == INT_DECLARATION)
        {
            Variable *var = get_variable_from_map(&vm, res.s[i].v.vd.name);
            if(var != 0) {
                err("Cannot create variable if it is already existing!");
                return;
            }
            add_variable_to_map(&vm, (Variable){res.s[i].v.vd.name, 0, 0, place});
            d("movl	$");printf("%d", res.s[i].v.vd.value);d(", -");printf("%d", place);d("(%rbp)");
            place += 4;
        }
        else if (res.s[i].type == INT_VALUE_ASSIGMENT)
        {
            Variable *var = get_variable_from_map(&vm, res.s[i].v.vd.name);
            if(var == 0) {
                err("Cannot find that variable!");
                return;
            }
            d("movl	$");printf("%d", res.s[i].v.vd.value);d(", -");printf("%d", var->place);d("(%rbp)");
        }
        else if (res.s[i].type == RETURN)
        {
            d("movl	$");printf("%d", res.s[i].v.ret.value);d(", %eax\n");
	        d("popq	%rbp\nret");
        }
        d("\n");
    }
}