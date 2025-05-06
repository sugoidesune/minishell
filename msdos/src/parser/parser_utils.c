/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:54:27 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/13 12:37:38 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/mini.h"

int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") ||!ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "unset"))
	{
		return (1);
	}
	return (0);
}

int	unexpected_token_error(t_mini *data, t_lexer *node)
{
	if (node != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
		if (node->type > 2)
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			ft_putstr_fd(node->token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

t_lexer	*error_check(t_mini *data)
{
	t_lexer	*node;

	node = data->lexer;
	if (node->type == PIPE || (node->type != WORD && !node->next))
		return (node);
	node = node->next;
	while (node)
	{
		if (node->type != WORD)
		{
			if (node->next == NULL)
				return (node);
			if (node->type == PIPE && node->next->type != PIPE)
			{
				node = node->next;
				continue ;
			}
			else if (node->next->type != WORD)
				return (node);
		}
		node = node->next;
	}
	return (NULL);
}

int	count_commands(t_mini *data, t_lexer *tmp)
{
	int		cmds_num;

	(void)data;
	cmds_num = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		cmds_num++;
		tmp = tmp->next;
	}
	return (cmds_num);
}
