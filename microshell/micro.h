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

#define REDIRECT_OUT_TRUNC 1
#define REDIRECT_OUT_APPEND 2
#define REDIRECT_IN 3

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,     // <
    TOKEN_REDIRECT_OUT,    // >
    TOKEN_HEREDOC,         // <<
    TOKEN_APPEND,          // >>
    TOKEN_SINGLE_QUOTE,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_VARIABLE
} t_token_type;

typedef struct s_redirection {
    t_list_el    *next;     // If you make a linked list of redirections
    t_list_el    *previous;
    t_token_type type;         // e.g., TOKEN_REDIRECT_IN, TOKEN_HEREDOC
    char         *filename;    // The target file or heredoc delimiter
} t_redirection;

// TEMP COMMAND MAKER
typedef struct s_command
{
    char	*command_name; // cat filename.txt
    char	**args; // {"cat", "filename.txt", NULL}]
    bool to_be_piped;
    t_list        *redirections; 
    int command_index;
    pid_t pid;

} t_command;
t_list *create_input_1();
t_list *create_input_2();
t_list *create_input_3();
t_list *create_input_4();
t_list *create_input_5();
t_list *create_input_6();
t_list *create_input_7();
void print_command_list(t_list *list);
void add_redirection(t_list *redirection_list, t_token_type redirection_type, char *redirection_filename);


//capture_input_micro.c
char	*capture_input(void);
void	parse_input(char *input, char **args);


// commands_lib.c
int count_commands(t_list *commands);


// path_finder.c
char *path_finder(char *command);

// builtins.c
bool bin_echo(char **args);