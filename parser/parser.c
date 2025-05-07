#include "../lexer/lexer.h"

void extract_args(t_token *token, char **args)
{
    char *input = token->value; // Assuming token->value contains the input string
    char *temp = strdup(input); // Duplicate the string to avoid modifying the original
    char *ptr = strtok(temp, " ");
    int i = 0;

    while (ptr != NULL)
    {
        args[i] = strdup(ptr);
        ptr = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL; // Null-terminate the array
    free(temp); // Free the duplicated string
}