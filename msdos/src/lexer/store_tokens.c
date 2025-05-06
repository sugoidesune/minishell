/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:05 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/10 13:28:29 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"
#include <stdlib.h>

int	store_right_brackets(char *input, t_lexer **token_list)
{
	t_lexer	*new_node;

	if (*(input + 1) == '>')
	{
		new_node = new_node_lexer(">>", APPEND);
		if (new_node == NULL)
			return (-1);
		add_node_lexer(new_node, token_list);
		return (2);
	}
	new_node = new_node_lexer(">", REDIR_OUT);
	if (new_node == NULL)
		return (-1);
	add_node_lexer(new_node, token_list);
	return (1);
}

int	store_left_brackets(char *input, t_lexer **token_list)
{
	t_lexer	*new_node;

	if (*(input + 1) == '<')
	{
		new_node = new_node_lexer("<<", HERE_DOC);
		if (new_node == NULL)
			return (-1);
		add_node_lexer(new_node, token_list);
		return (2);
	}
	new_node = new_node_lexer("<", REDIR_IN);
	if (new_node == NULL)
		return (-1);
	add_node_lexer(new_node, token_list);
	return (1);
}

int	store_word(char *input, t_lexer **token_list)
{
	int		end;
	int		s_quote;
	int		d_quote;
	t_lexer	*new_node;

	end = 0;
	s_quote = 0;
	d_quote = 0;
	while (input[end])
	{
		if (input[end] == '\'')
			s_quote = !s_quote;
		else if (input[end] == '\"')
			d_quote = !d_quote;
		else if ((input[end] == '<' || input[end] == '>' || input[end] == '|'
				|| is_whitespace(input[end])) && s_quote == 0 && d_quote == 0)
			break ;
		end++;
	}
	new_node = new_node_lexer(ft_substr(input, 0, end), WORD);
	if (new_node == NULL)
		return (-1);
	add_node_lexer(new_node, token_list);
	return (end);
}

int	store_token(char *input, t_mini *data)
{
	t_lexer	*new_node;

	if (*input == '<')
		return (store_left_brackets(input, &data->lexer));
	else if (*input == '>')
		return (store_right_brackets(input, &data->lexer));
	else if (*input == '|')
	{
		new_node = new_node_lexer("|", PIPE);
		if (new_node == NULL)
			return (-1);
		add_node_lexer(new_node, &data->lexer);
	}
	else
		return (store_word(input, &data->lexer));
	return (1);
}
