/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:54 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/16 11:18:50 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*expand_and_reassemble(t_mini *data, char *string, \
t_xy xy, char *expansion)
{
	char	*before_var;
	char	*after_var;
	char	*tmp;

	tmp = NULL;
	after_var = NULL;
	before_var = ft_substr(string, 0, xy.start - 1);
	if (string[xy.end + 1] == '\0')
	{
		string = ft_strjoin(before_var, expansion);
		data->exp_idx = (int)ft_strlen(string) - 1;
	}
	else
	{
		after_var = ft_substr(string, xy.end + 1, \
		ft_strlen(string) - xy.end - 1);
		tmp = ft_strjoin(before_var, expansion);
		data->exp_idx = (int)ft_strlen(tmp) - 1;
		string = ft_strjoin(tmp, after_var);
		free(after_var);
		free(tmp);
	}
	free(before_var);
	return (string);
}

char	*mark_expansion(char *expansion)
{
	char	*tmp;
	char	*string;

	tmp = ft_strjoin("\x02", expansion);
	string = ft_strjoin(tmp, "\x02");
	free(tmp);
	return (string);
}

char	*expand_var(t_mini *data, char *string, t_xy xy, char *expansion)
{
	char	*tmp;

	if (xy.start == 1 && string[xy.end + 1] == '\0')
	{
		data->exp_idx = (int)ft_strlen(expansion) + 1;
		string = mark_expansion(expansion);
	}
	else
	{
		tmp = mark_expansion(expansion);
		string = expand_and_reassemble(data, string, xy, tmp);
		free(tmp);
	}
	return (string);
}

char	*expand_substring(t_mini *data, char *string, int start, int end)
{
	t_env	*tmp;
	char	*substring;
	char	*tmp_var;
	t_xy	xy;

	xy.start = start;
	xy.end = end;
	tmp = data->env_list;
	substring = ft_substr(string, start, end - start + 1);
	while (tmp)
	{
		tmp_var = ft_substr(tmp->variable, 0, ft_strlen(tmp->variable) - 1);
		if (!ft_strcmp(tmp_var, substring) && tmp->content)
		{
			free(tmp_var);
			free (substring);
			return (expand_var(data, string, xy, tmp->content));
		}
		tmp = tmp->next;
		free(tmp_var);
	}
	free(substring);
	return (unmatched_var(data, string, start, end));
}
