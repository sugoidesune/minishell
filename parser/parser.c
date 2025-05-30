#include "../lexer/lexer.h"
#include <stdlib.h> // For malloc, free (assuming these are allowed, as per prompt)
// #include "libft.h" // For ft_strdup, ft_lstnew, ft_lstadd_back etc. (ensure this is correctly included)
// #include "listlib.h" // If t_list operations are defined here

// Forward declarations for helper functions
static t_command	*create_command_node(void);
static int			add_argument_to_list(t_list **arg_list, char *value);
static char			**convert_arg_list_to_array(t_list *arg_list);
static int			add_redirection_to_command(t_command *cmd,
						t_token_type type, char *filename);

// Main parser function
t_command *parse_tokens(t_token *token_list)
{
	t_command	*command_head;
	t_command	*current_cmd;
	t_list		*current_args_list;
	t_token		*current_token;

	command_head = NULL;
	current_cmd = NULL;
	current_args_list = NULL;
	current_token = token_list;
	if (!current_token)
		return (NULL);
	// Create the first command node
	current_cmd = create_command_node();
	if (!current_cmd)
		return (NULL); // Handle malloc failure
	command_head = current_cmd;
	// current_cmd->redirections = ft_lstnew(NULL); // Initialize redirection list if using listlib

	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_WORD)
		{
			if (!add_argument_to_list(&current_args_list, current_token->value))
			{
				// Handle ft_strdup or ft_lstnew failure
				// free_command_list(command_head); // Implement cleanup
				// ft_lstclear(&current_args_list, free); // Clear temporary args
				return (NULL);
			}
		}
		else if (current_token->type == TOKEN_REDIRECT_IN
			|| current_token->type == TOKEN_REDIRECT_OUT
			|| current_token->type == TOKEN_HEREDOC
			|| current_token->type == TOKEN_APPEND)
		{
			if (current_token->next == NULL
				|| current_token->next->type != TOKEN_WORD)
			{
				// Syntax error: redirection without filename
				// printf("Syntax error: missing filename after redirection\n");
				// free_command_list(command_head);
				// ft_lstclear(&current_args_list, free);
				return (NULL);
			}
			if (!add_redirection_to_command(current_cmd, current_token->type,
					current_token->next->value))
			{
				// Handle malloc failure in redirection
				// free_command_list(command_head);
				// ft_lstclear(&current_args_list, free);
				return (NULL);
			}
			current_token = current_token->next; // Consume filename token
		}
		else if (current_token->type == TOKEN_PIPE)
		{
			current_cmd->args = convert_arg_list_to_array(current_args_list);
			// ft_lstclear(&current_args_list, NULL); // Clear list wrapper, not content if moved
			current_args_list = NULL; // Reset for next command
			if (current_token->next == NULL)
			{
				// Syntax error: pipe at end of input
				// printf("Syntax error: unexpected pipe at end of input\n");
				// free_command_list(command_head);
				return (NULL);
			}
			current_cmd->next = create_command_node();
			if (!current_cmd->next)
			{
				// Handle malloc failure
				// free_command_list(command_head);
				return (NULL);
			}
			current_cmd->next->prev = current_cmd;
			current_cmd = current_cmd->next;
			// current_cmd->redirections = ft_lstnew(NULL); // Init redirection list
		}
		current_token = current_token->next;
	}
	// Finalize the last command's arguments
	if (current_cmd != NULL) // Ensure current_cmd is valid
	{
		current_cmd->args = convert_arg_list_to_array(current_args_list);
		// ft_lstclear(&current_args_list, NULL); // Clear list wrapper
	}
	return (command_head);
}

// Helper to create and initialize a t_command node
static t_command *create_command_node(void)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->redirections = NULL; // Initialize as NULL or to an empty list
	new_cmd->heredoc_name = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	// If using listlib for redirections:
	// new_cmd->redirections = ft_lstnew(NULL); // Create an empty list sentinel or similar
	// if (!new_cmd->redirections) { free(new_cmd); return NULL; }
	return (new_cmd);
}

// Helper to add an argument string to a temporary list
// Assumes ft_strdup and ft_lstnew, ft_lstadd_back are available from libft
static int add_argument_to_list(t_list **arg_list, char *value)
{
	char	*arg_copy;
	t_list	*new_node;

	// arg_copy = ft_strdup(value); // Use your libft's ft_strdup
	// if (!arg_copy)
	// 	return (0); // Failure
	// new_node = ft_lstnew(arg_copy);
	// if (!new_node)
	// {
	// 	free(arg_copy);
	// 	return (0); // Failure
	// }
	// ft_lstadd_back(arg_list, new_node);
	(void)arg_list; // Suppress unused parameter warning if not using libft list
	(void)value;    // Suppress unused parameter warning
	// Placeholder: actual implementation depends on your list library (t_list)
	// For now, this is a stub. You'll need to implement this using your listlib.h
	// or manage a dynamic array directly (more complex without realloc).
	return (1); // Success
}

// Helper to convert the temporary list of arguments to char**
// Assumes ft_lstsize and list iteration from libft
static char **convert_arg_list_to_array(t_list *arg_list)
{
	char	**args_array;
	int		size;
	int		i;
	t_list	*current;

	// size = ft_lstsize(arg_list);
	// args_array = (char **)malloc(sizeof(char *) * (size + 1));
	// if (!args_array)
	// 	return (NULL);
	// i = 0;
	// current = arg_list;
	// while (current != NULL)
	// {
	// 	args_array[i] = (char *)current->content; // Assumes content is the char*
	// 	current = current->next;
	// 	i++;
	// }
	// args_array[i] = NULL;
	(void)arg_list; // Suppress unused parameter warning
	// Placeholder: actual implementation depends on your list library.
	// The list nodes' content (strings) are moved, not copied again here.
	// The list itself (nodes, not content) should be cleared afterwards.
	args_array = NULL; // Stub
	return (args_array);
}

// Helper to add a redirection to the command's redirection list
static int add_redirection_to_command(t_command *cmd, t_token_type type,
		char *filename)
{
	t_redirection	*redir;
	// t_list_el		*new_redir_node; // Assuming t_list_el is your list node for t_list

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (0); // Malloc failure
	redir->type = type;
	// redir->filename = ft_strdup(filename); // Use your libft's ft_strdup
	// if (!redir->filename)
	// {
	// 	free(redir);
	// 	return (0); // Malloc failure
	// }
	redir->next = NULL;
	redir->prev = NULL;

	// Add to cmd->redirections list (implementation depends on your listlib.h)
	// Example if cmd->redirections is a t_list from libft:
	// new_redir_node = ft_lstnew(redir);
	// if (!new_redir_node) {
	//     free(redir->filename);
	//     free(redir);
	//     return (0);
	// }
	// ft_lstadd_back(&(cmd->redirections), new_redir_node);
	(void)cmd; // Suppress unused parameter warning
	(void)filename; // Suppress unused parameter warning
	// Placeholder: This needs to be implemented using your listlib for cmd->redirections
	return (1); // Success
}

/*
Note: You will need to implement or uncomment the parts that use your specific
list library functions (e.g., ft_lstnew, ft_lstadd_back, ft_lstsize, ft_lstclear from your libft.h or listlib.h)
and ft_strdup. Also, robust error handling (freeing allocated memory on failure) is crucial.
The example above provides a skeleton; you'll need to fill in the details
according to your library and error handling strategy.
*/