/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:47:32 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 22:43:53 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*env_expand(t_mini *data, char **tmp, char **string)
{
	int	j;
	int	i;

	i = data->exp_idx;
	if ((*tmp)[i] == '\0' || is_whitespace((*tmp)[i]))
		return (*tmp);
	free (*string);
	if ((*tmp)[i] == '?')
		*string = handle_question_mark(data, *tmp, i, data->exit_code);
	else
	{
		j = i;
		while ((*tmp)[j] && (*tmp)[j] != '$' \
		&& !is_whitespace((*tmp)[j]) && !is_quote((*tmp)[j]) \
		&& !is_delim((*tmp)[j]))
			j++;
		*string = expand_substring(data, *tmp, i, j - 1);
	}
	free(*tmp);
	*tmp = ft_strdup(*string);
	return (*tmp);
}

void	expand_string(t_mini *data, char **string)
{
	int		single_quote;
	int		double_quote;
	char	*tmp;

	data->exp_idx = 0;
	single_quote = 0;
	double_quote = 0;
	tmp = ft_strdup(*string);
	while (tmp[data->exp_idx])
	{
		if (tmp[data->exp_idx] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (tmp[data->exp_idx] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		else if (tmp[data->exp_idx] == '$' && single_quote == 0)
		{
			data->exp_idx++;
			tmp = env_expand(data, &tmp, string);
			continue ;
		}
		data->exp_idx++;
	}
	free(tmp);
}

void	mark_quotes(t_parser *cmd, int i)
{
	int	j;
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (cmd)
	{
		i = -1;
		while (cmd->commands && cmd->commands[++i])
		{
			j = 0;
			while (cmd->commands[i][j])
			{
				if (cmd->commands[i][j] == '\'' && !in_double)
					in_single = !in_single;
				if (cmd->commands[i][j] == '\"' && !in_single)
					in_double = !in_double;
				if (cmd->commands[i][j] == ' ' && (in_double || in_single))
					cmd->commands[i][j] = '\x05';
				j++;
			}
		}
		cmd = cmd->next;
	}
}

int	clean_all(t_mini *data)
{
	t_parser	*cmd;

	cmd = data->parser;
	clean_spaces(data);
	mark_quotes(cmd, -1);
	clean_quotes(data);
	clean_markers(data);
	return (0);
}

int	expander(t_mini *data)
{
	t_parser	*tmp;
	char		**cmd_tmp;
	int			i;

	tmp = data->parser;
	while (tmp)
	{
		i = -1;
		while (tmp->commands && tmp->commands[++i])
		{
			if (!ft_strcmp(tmp->commands[i], "\"$\""))
				continue ;
			expand_string(data, &tmp->commands[i]);
		}
		if (expand_redirections(data, tmp))
			return (1);
		if (tmp->commands)
		{
			cmd_tmp = strarr_cpy(tmp->commands);
			free_strarr(tmp->commands);
			tmp->commands = cmd_tmp;
		}
		tmp = tmp->next;
	}
	return (clean_all(data));
}
