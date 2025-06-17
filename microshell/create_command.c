/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:19:47 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/17 18:29:21 by tbatis           ###   ########.fr       */
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
        cmd1_cat->redirection = 0;
        cmd1_cat->command_index = 0;
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
        cmd2_rev->redirection = 0;
        cmd2_rev->command_index = 1;
        ft_list_append_new(list_instance, cmd2_rev);
    }
    
    return (list_instance);
}

t_list *create_input_2(void)
{
    t_list      *list_instance;
    t_command   *cmd1_ls;
    t_command   *cmd2_grep;
    t_command   *cmd3_wc;
    char        **args_ls;
    char        **args_grep;
    char        **args_wc;

    list_instance = ft_new_list();
    if (list_instance == NULL)
        return (NULL);
    
    cmd1_ls = NULL;
    cmd2_grep = NULL;
    cmd3_wc = NULL;
    args_ls = NULL;
    args_grep = NULL;
    args_wc = NULL;

    // Create t_command for "ls -la" (tests PATH lookup)
    cmd1_ls = malloc(sizeof(t_command));
    if (cmd1_ls != NULL)
    {
        cmd1_ls->command_name = ft_strdup("ls");
        args_ls = malloc(sizeof(char*) * 3);
        if (args_ls != NULL)
        {
            args_ls[0] = ft_strdup("ls");
            args_ls[1] = ft_strdup("-la");
            args_ls[2] = NULL;
        }
        cmd1_ls->args = args_ls;
        cmd1_ls->to_be_piped = true;
        cmd1_ls->redirection = 0;
        cmd1_ls->command_index = 0;
        ft_list_append_new(list_instance, cmd1_ls);
    }

    // Create t_command for "grep .c" (tests PATH lookup and actually processes input)
    cmd2_grep = malloc(sizeof(t_command));
    if (cmd2_grep != NULL)
    {
        cmd2_grep->command_name = ft_strdup("grep");
        args_grep = malloc(sizeof(char*) * 3);
        if (args_grep != NULL)
        {
            args_grep[0] = ft_strdup("grep");
            args_grep[1] = ft_strdup("\\.c");
            args_grep[2] = NULL;
        }
        cmd2_grep->args = args_grep;
        cmd2_grep->to_be_piped = true;
        cmd2_grep->redirection = 0;
        cmd2_grep->command_index = 1;
        ft_list_append_new(list_instance, cmd2_grep);
    }

    // Create t_command for "wc -l" (tests PATH lookup and counts lines)
    cmd3_wc = malloc(sizeof(t_command));
    if (cmd3_wc != NULL)
    {
        cmd3_wc->command_name = ft_strdup("wc");
        args_wc = malloc(sizeof(char*) * 3);
        if (args_wc != NULL)
        {
            args_wc[0] = ft_strdup("wc");
            args_wc[1] = ft_strdup("-l");
            args_wc[2] = NULL;
        }
        cmd3_wc->args = args_wc;
        cmd3_wc->to_be_piped = false;
        cmd3_wc->redirection = 0;
        cmd3_wc->command_index = 2;
        ft_list_append_new(list_instance, cmd3_wc);
    }
    
    return (list_instance);
}

t_list *create_input_3(void)
{
    t_list      *list_instance;
    t_command   *cmd1_echo;
    char        **args_echo;

    list_instance = ft_new_list();
    if (list_instance == NULL)
        return (NULL);
    
    cmd1_echo = NULL;
    args_echo = NULL;

    // Create t_command for "echo haha >> .text"
    cmd1_echo = malloc(sizeof(t_command));
    if (cmd1_echo != NULL)
    {
        cmd1_echo->command_name = ft_strdup("echo");
        args_echo = malloc(sizeof(char*) * 3);
        if (args_echo != NULL)
        {
            args_echo[0] = ft_strdup("echo");
            args_echo[1] = ft_strdup("haha");
            args_echo[2] = NULL;
        }
        cmd1_echo->args = args_echo;
        cmd1_echo->to_be_piped = false;
        cmd1_echo->redirection = 2;
        cmd1_echo->redirect_file = ft_strdup("TEXTFILE");
        cmd1_echo->command_index = 0;
        ft_list_append_new(list_instance, cmd1_echo);
    }
    
    return (list_instance);
}
t_list *create_input_4(void)
{
    t_list      *list_instance;
    t_command   *cmd1_ls;
    t_command   *cmd2_grep;
    char        **args_ls;
    char        **args_grep;

    list_instance = ft_new_list();
    if (list_instance == NULL)
        return (NULL);
    
    cmd1_ls = NULL;
    cmd2_grep = NULL;
    args_ls = NULL;
    args_grep = NULL;

    // Create t_command for "ls -la" (generates text output)
    cmd1_ls = malloc(sizeof(t_command));
    if (cmd1_ls != NULL)
    {
        cmd1_ls->command_name = ft_strdup("ls");
        args_ls = malloc(sizeof(char*) * 3);
        if (args_ls != NULL)
        {
            args_ls[0] = ft_strdup("ls");
            args_ls[1] = ft_strdup("-la");
            args_ls[2] = NULL;
        }
        cmd1_ls->args = args_ls;
        cmd1_ls->to_be_piped = true;
        cmd1_ls->redirection = 3;
        cmd1_ls->command_index = 0;
        ft_list_append_new(list_instance, cmd1_ls);
    }

    // Create t_command for "grep micro" (filters ls output and redirects to LOGS)
    cmd2_grep = malloc(sizeof(t_command));
    if (cmd2_grep != NULL)
    {
        cmd2_grep->command_name = ft_strdup("grep");
        args_grep = malloc(sizeof(char*) * 3);
        if (args_grep != NULL)
        {
            args_grep[0] = ft_strdup("grep");
            args_grep[1] = ft_strdup("micro");
            args_grep[2] = NULL;
        }
        cmd2_grep->args = args_grep;
        cmd2_grep->to_be_piped = false;
        cmd2_grep->redirection = 1;
        cmd2_grep->redirect_file = ft_strdup("LOGS");
        cmd2_grep->command_index = 1;
        ft_list_append_new(list_instance, cmd2_grep);
    }
    
    return (list_instance);
}

t_list *create_input_5(void)
{
    t_list      *list_instance;
    t_command   *cmd1_echo;
    t_command   *cmd2_cat;
    char        **args_echo;
    char        **args_cat;

    list_instance = ft_new_list();
    if (list_instance == NULL)
        return (NULL);
    
    cmd1_echo = NULL;
    cmd2_cat = NULL;
    args_echo = NULL;
    args_cat = NULL;

    // Create t_command for "echo hello world"
    cmd1_echo = malloc(sizeof(t_command));
    if (cmd1_echo != NULL)
    {
        cmd1_echo->command_name = ft_strdup("echo");
        args_echo = malloc(sizeof(char*) * 4);
        if (args_echo != NULL)
        {
            args_echo[0] = ft_strdup("echo");
            args_echo[1] = ft_strdup("hello");
            args_echo[2] = ft_strdup("world");
            args_echo[3] = NULL;
        }
        cmd1_echo->args = args_echo;
        cmd1_echo->to_be_piped = true;
        cmd1_echo->redirection = 0;
        cmd1_echo->command_index = 0;
        ft_list_append_new(list_instance, cmd1_echo);
    }

    // Create t_command for "cat" (receives input from pipe)
    cmd2_cat = malloc(sizeof(t_command));
    if (cmd2_cat != NULL)
    {
        cmd2_cat->command_name = ft_strdup("cat");
        args_cat = malloc(sizeof(char*) * 2);
        if (args_cat != NULL)
        {
            args_cat[0] = ft_strdup("cat");
            args_cat[1] = NULL;
        }
        cmd2_cat->args = args_cat;
        cmd2_cat->to_be_piped = false;
        cmd2_cat->redirection = 0;
        cmd2_cat->command_index = 1;
        ft_list_append_new(list_instance, cmd2_cat);
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
        if (cmd->redirection > 0)
            printf(">>redirect>>\n");
        
        printf("\n");
        current = current->next;
    }
}
