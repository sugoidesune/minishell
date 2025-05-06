/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:00:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/05/06 18:14:15 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

void process_input(char *input)
{
    t_token	*tokens;
    t_token	*current;
    
    tokens = lexer(input);
    current = tokens;
    while (current)
    {
        print_token_info(current);
        current = current->next;
    }
    
    free_tokens(tokens);
}

void welcome_message(void)
{
    printf("\n%s%s ╔══════════════════════════╗%s\n", BOLD, BLUE, RESET);
    printf("%s%s ║                          ║%s\n", BOLD, BLUE, RESET);
    printf("%s%s ║  %s%s Welcome to %s%sMiniHell%s%s!   %s%s║%s\n", 
           BOLD, BLUE, RESET, BOLD, CYAN, WHITE, CYAN, RESET, BOLD, BLUE, RESET);
    printf("%s%s ║                          ║%s\n", BOLD, BLUE, RESET);
    printf("%s%s ╚══════════════════════════╝%s\n\n", BOLD, BLUE, RESET);
}

int main(void)
{
    char *input;
    
    welcome_message();
    while (1)
    {
        input = readline("\001\033[32mminishell>\033[0m\002");
        if (!input)
        {
            printf("%s%sexit%s\n", BOLD, YELLOW, RESET);
            break;
        }
        rl_on_new_line();
        if (*input)
        {
            add_history(input);
            process_input(input);
        }
        rl_replace_line("", 0);
        rl_redisplay();
        
        free(input);
    }
    return (0);
}
