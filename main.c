/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:00:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/27 18:40:16 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
// #include "parser/parser.h" // Will be used when parser is implemented

// ANSI color codes
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Background color codes
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Animation frames for the spinning cursor
const char *spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};

char *get_colorful_prompt(void)
{
    char *username;
    char hostname[256];
    static char prompt[256];
    static int color_cycle = 0;
    const char *color_codes[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};
    
    // Get username
    username = getenv("USER");
    if (!username)
        username = "user";
    
    // Get hostname
    if (gethostname(hostname, sizeof(hostname)) != 0)
        strcpy(hostname, "minishell");
    
    // Truncate hostname at first '.'
    char *dot = strchr(hostname, '.');
    if (dot)
        *dot = '\0';
    
    // Create colorful prompt with rainbow effect
    snprintf(prompt, sizeof(prompt), 
             "%s%s%s%s@%s%s%s %s%s➜%s %s%s$%s ",
             BOLD, color_codes[color_cycle % 6], username, RESET,
             BOLD, color_codes[(color_cycle + 2) % 6], hostname, RESET,
             BOLD, RESET,
             BOLD, color_codes[(color_cycle + 4) % 6], RESET);  
    
    return prompt;
}

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

void display_welcome_message(void)
{
    printf("\n%s%s╔══════════════════════════════════════════╗%s\n", BOLD, MAGENTA, RESET);
    printf("%s%s║                                          ║%s\n", BOLD, MAGENTA, RESET);
    printf("%s%s║  %s%s Welcome to %s%sMiniShell%s%s!                  %s%s║%s\n", 
           BOLD, MAGENTA, RESET, BOLD, CYAN, WHITE, CYAN, RESET, BOLD, MAGENTA, RESET);
    printf("%s%s║  %s%s A tiny shell with big capabilities     %s%s║%s\n", 
           BOLD, MAGENTA, RESET, BOLD, BOLD, MAGENTA, RESET);
    printf("%s%s║                                          ║%s\n", BOLD, MAGENTA, RESET);
    printf("%s%s╚══════════════════════════════════════════╝%s\n\n", BOLD, MAGENTA, RESET);
}

int main(void)
{
    char *input;
    
    display_welcome_message();
    while (1)
    {
        input = readline(get_colorful_prompt());
        if (!input)
        {
            printf("%s%sexit%s\n", BOLD, YELLOW, RESET);
            break;
        }
        
        if (*input)
        {
            add_history(input);
            process_input(input);
        }
        
        free(input);
    }
    
    return (0);
}
