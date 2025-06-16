#include "micro.h"

bool bin_echo(char **args)
{
    printf("%s\n", args[1]);
    return true;
}