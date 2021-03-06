#include <stdio.h>

#include "types.h"
#include "file_reader.h"
#include "utils.h"
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"

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
