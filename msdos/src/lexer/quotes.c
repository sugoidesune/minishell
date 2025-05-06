/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:16 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 19:02:35 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_double_quoted(char *str)
{
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	return (0);
}

int	is_single_quoted(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (1);
	return (0);
}

int	store_token_in_quotes(char *input, t_lexer **token_list)
{
	int		end;
	t_lexer	*new_node;

	end = 1;
	if (input[0] == '\'')
		while (input[end] && !(input[end] == '\'' && (input[end + 1] == '\0'
					|| input[end + 1] == ' ')))
			end++;
	else if (input[0] == '\"')
		while (input[end] && !(input[end] == '\"' && (input[end + 1] == '\0'
					|| input[end + 1] == ' ')))
			end++;
	new_node = new_node_lexer(ft_substr(input, 0, end + 1), WORD);
	if (new_node == NULL)
		return (-1);
	add_node_lexer(new_node, token_list);
	return (end + 1);
}

int	count_quotes(t_mini *data, char *line)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && !in_single)
			in_double = !in_double;
		else if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	if (in_single || in_double)
	{
		ft_putstr_fd("quotes not properly closed\n", 2);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}
