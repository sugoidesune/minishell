#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h" 
#include "listlib/list.h"
#include <string.h> // For strtok. Note: strtok is not in the allowed functions list.
#include <sys/wait.h>
#include <unistd.h>
// include for O_WRONLY | O_CREAT | O_TRUNC,
#include <fcntl.h>

# define IS_CHILD_PROCESS 0

# define INPUT_FD 0
# define OUTPUT_FD 1

// TEMP COMMAND MAKER
typedef struct s_command
{
    char	*command_name;
    char	**args;
    bool to_be_piped;
    int redirection;
    char *redirect_file;
    int command_index;
    pid_t pid;

} t_command;
t_list *create_input_1();
t_list *create_input_2();
t_list *create_input_3();
t_list *create_input_4();
void print_command_list(t_list *list);


//capture_input_micro.c
char	*capture_input(void);
void	parse_input(char *input, char **args);


// commands_lib.c
int count_commands(t_list *commands);


// path_finder.c
char *path_finder(char *command);

// builtins.c
bool bin_echo(char **args);