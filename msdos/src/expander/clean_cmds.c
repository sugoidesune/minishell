/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:13:21 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 14:18:04 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	count_marker(char *str, char marker)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == marker)
			count++;
		i++;
	}
	return (count);
}

void	clean_markers_redir(t_mini *data, t_parser *node)
{
	t_lexer	*redir;

	redir = node->redirections;
	while (redir)
	{
		redir->token = remove_marker(data, redir->token, \
		count_marker(redir->token, '\x02'), '\x02');
		redir->token = remove_marker(data, redir->token, \
		count_marker(redir->token, '\x05'), '\x05');
		redir = redir->next;
	}
}

void	clean_markers(t_mini *data)
{
	t_parser	*node;
	int			i;

	node = data->parser;
	while (node)
	{
		i = 0;
		while (node->commands && node->commands[i])
		{
			node->commands[i] = remove_marker(data, node->commands[i], \
			count_marker(node->commands[i], '\x02'), '\x02');
			i++;
		}
		clean_markers_redir(data, node);
		node = node->next;
	}
}

void	clean_spaces(t_mini *data)
{
	t_parser	*node;
	int			i;

	node = data->parser;
	while (node)
	{
		i = 0;
		while (node->commands && node->commands[i])
		{
			clean_cmd(node->commands[i]);
			i++;
		}
		node = node->next;
	}
}

void	clean_cmd(char *cmd)
{
	int	i;
	int	in_double;
	int	in_var;

	in_double = 0;
	in_var = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			in_double = !in_double;
		if (cmd[i] == '\x02')
			in_var = !in_var;
		if (cmd[i] == ' ' && in_double && in_var)
			cmd[i] = '\x03';
		i++;
	}
}
