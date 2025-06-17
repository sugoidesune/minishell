#include "micro.h"

bool bin_echo(char **args)
{
    int i = 1;
    while (args[i] != NULL)
    {
        if (i > 1)
            printf(" ");
        printf("%s", args[i]);
        i++;
    }
    printf("\n");
    return true;
}