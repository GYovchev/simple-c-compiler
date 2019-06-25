#include <stdio.h>

#include "file_reader.h"
#include "utils.h"

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
    char *c;
    do
    {
        c = next_char(NULL);
        if (c != NULL)
            printf("%c", *c);
    } while (c != NULL);
}