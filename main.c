/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:00:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/27 18:23:56 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
// #include "parser/parser.h" // Will be used when parser is implemented

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

int main(void)
{
	char *input;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
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
