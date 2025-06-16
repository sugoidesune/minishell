#include "micro.h"

//a function that loops through an array of strings.
// it should take a function validator,
// each string gets passed to validator.
// if validator returns true, return the string early.
// if validator returns false, keep looping.
// if we reach the end of the array (terminated with NULL)
// then we return an empty string.
char *find_first_valid_string(char **strings, bool (*validator)(char *))
{
    int i;
    
    i = 0;
    if (!strings || !validator)
        return ("");
    
    while (strings[i] != NULL)
    {
        if (validator(strings[i]))
            return (ft_strdup(strings[i]));
        i++;
    }
    return ("");
}