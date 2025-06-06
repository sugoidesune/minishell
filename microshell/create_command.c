/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:19:47 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/05 22:16:16 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro.h"

// This function creates and returns a t_list by value.
// The list will contain t_command structs representing the sequence:
// 1. "cat /hosts" (output piped to the next command)
// 2. "rev"        (receives input from pipe, output not piped further in this group)
// The t_command structs and their internal strings (command_name, args)
// are allocated on the heap.
// Assumes ft_strdup is available from libft.h.
// Note: This implementation assumes malloc/ft_strdup succeed.
// Proper error handling for allocations should be added for robust code.
t_list *create_input_1(void)
{
    t_list      *list_instance;
    t_command   *cmd1_cat;
    t_command   *cmd2_rev;
    char        **args_cat;
    char        **args_rev;

    list_instance = ft_new_list();
    if (list_instance == NULL)
        return (NULL);
    
    cmd1_cat = NULL;
    cmd2_rev = NULL;
    args_cat = NULL;
    args_rev = NULL;

    // Create t_command for "cat /hosts"
    cmd1_cat = malloc(sizeof(t_command));
    if (cmd1_cat != NULL)
    {
        cmd1_cat->command_name = ft_strdup("cat");
        args_cat = malloc(sizeof(char*) * 3);
        if (args_cat != NULL)
        {
            args_cat[0] = ft_strdup("cat");
            args_cat[1] = ft_strdup("./hosts");
            args_cat[2] = NULL;
        }
        cmd1_cat->args = args_cat;
        cmd1_cat->to_be_piped = true;
        cmd1_cat->to_be_redirected = false;
        ft_list_append_new(list_instance, cmd1_cat);
    }

    // Create t_command for "rev"
    cmd2_rev = malloc(sizeof(t_command));
    if (cmd2_rev != NULL)
    {
        cmd2_rev->command_name = ft_strdup("rev");
        args_rev = malloc(sizeof(char*) * 2);
        if (args_rev != NULL)
        {
            args_rev[0] = ft_strdup("rev");
            args_rev[1] = NULL;
        }
        cmd2_rev->args = args_rev;
        cmd2_rev->to_be_piped = false;
        cmd2_rev->to_be_redirected = false;
        ft_list_append_new(list_instance, cmd2_rev);
    }
    
    return (list_instance);
}

void print_command_list(t_list *list)
{
    t_list_el *current;
    t_command *cmd;
    int i;

    current = list->head;
    while (current != NULL)
    {
        i = 0;
        cmd = (t_command *)current->content;
        printf("Command: %s\n", cmd->command_name);
        
        printf("Arguments: ");
        while (cmd->args && cmd->args[i])
        {
            printf("%s ", cmd->args[i]);
            i++;
        }
        printf("\n");

        if (cmd->to_be_piped)
            printf("|piped|\n");
        if (cmd->to_be_redirected)
            printf(">>redirect>>\n");
        
        printf("\n");
        current = current->next;
    }
}
