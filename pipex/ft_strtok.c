

char *ft_strtok(char *str, const char *delim)
{
    char *start;
    static char *string;
    char *end;

    start = str;
    if(!str)
        start = string;
    
    while(*str)
    {
        if(*str == *delim)
        {
            end = str;
            while(*str == *delim)
            {
                str++;
                delim++;
            }
            if(delim == '\0' && *str)
            {
                string++;
            }
            
        }
    }
}