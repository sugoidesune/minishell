/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:43:02 by mmusic            #+#    #+#             */
/*   Updated: 2025/04/10 17:41:38 by mmusic           ###   ########.fr       */
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
	if (!input)
		return (NULL);
	if (ft_strlen(input) == 0)
	{
		write(2, "Error: Empty input\n", 20);
		return (NULL);
	}
	if (validate_quotes(input) == -1)
	{
		write(2, "Error: Unmatched quotes\n", 24);
		return (NULL);
	}
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
			head = process_single_quotes(&str, head, &token);
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