/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:43:02 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/19 17:16:25 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*token;
	char	*str;

	head = NULL;
	token = NULL;
	str = input;
	while (*str)
	{
		skip_whitespace(&str);
		if (!*str)
			break;
		if (*str == '|')
			head = add_token_to_list(head, &token, TOKEN_PIPE, "|");
		else if (*str == '<')
			head = process_redirect_in(&str, head, &token);
		else if (*str == '>')
			head = process_redirect_out(&str, head, &token);
		else if (*str == '\'')
			head = add_token_to_list(head, &token, TOKEN_SINGLE_QUOTE, "'");
		else if (*str == '"')
			head = process_double_quotes(&str, head, &token);
		else if(*str == '$')
			head = process_variable(&str, head, &token);
		else
			head = process_word(&str, head, &token);
		str++;
	}
	return (head);
}

void print_token_info(t_token *token)
{
	t_subtoken *subtoken;
	
	printf("type: %d, value: '%s'\n", token->type, token->value);
	if (token->subtoken)
	{
		printf("  Contains subtokens:\n");
		subtoken = token->subtoken;
		while (subtoken)
		{
			printf("    subtype: %d, subvalue: '%s'\n", 
				subtoken->type, subtoken->value);
			subtoken = subtoken->next;
		}
	}
}

int	main(int argc, char **argv)
{
	t_token	*token;
    t_token	*head;

    token = NULL;
    head = NULL;
    if (argc != 2)
    {
		printf("Usage: %s \"command\"\n", argv[0]);
		return (1);
	}
	head = lexer(argv[1]);
	token = head;
	while (token)
	{
		print_token_info(token);
		token = token->next;
    }
	free_tokens(head);	
	return (0);
}