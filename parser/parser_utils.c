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