#include "../lexer/lexer.h"

t_command *create_new_command_node(void) {
    t_command *new_cmd = (t_command *)malloc(sizeof(t_command));
    if (!new_cmd)
        return (NULL); // Handle allocation error
    new_cmd->args = NULL; // Initialize properly
    new_cmd->redirections = ft_new_list(); // Use your listlib
    if (!new_cmd->redirections)
    {
        free(new_cmd);
        return (NULL); // Handle allocation error
    }
    new_cmd->next = NULL;
    new_cmd->prev = NULL;
    // Initialize other fields (is_builtin, heredoc_name) if you have them
    return (new_cmd);
}

void free_command_node(t_command *cmd) {
    if (cmd) {
        if (cmd->args) {
            for (int i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        ft_free_list(cmd->redirections); // Use your listlib
        free(cmd);
    }
}

void add_args_command_node(t_command *cmd, char *arg) {
    if (!cmd || !arg)
        return; // Handle error
    size_t len = 0;
    while (cmd->args && cmd->args[len])
        len++;
    char **new_args = (char **)malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return; // Handle allocation error
    for (size_t i = 0; i < len; i++)
        new_args[i] = cmd->args[i];
    new_args[len] = ft_strdup(arg);
    new_args[len + 1] = NULL;
    free(cmd->args);
    cmd->args = new_args;
}