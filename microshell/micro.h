#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h" 
#include "listlib/list.h"
#include <string.h> // For strtok. Note: strtok is not in the allowed functions list.
#include <sys/wait.h>
#include <unistd.h>


// TEMP COMMAND MAKER
typedef struct s_command
{
    char	*command_name;
    char	**args;
    bool to_be_piped;
    bool to_be_redirected;
    int command_index;

} t_command;
t_list *create_input_1();
void print_command_list(t_list *list);


//capture_input_micro.c
char	*capture_input(void);
void	parse_input(char *input, char **args);


// commands_lib.c
int count_commands(t_list *commands);