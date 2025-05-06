/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:42:18 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 14:08:32 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	replace_and_reset(char *str, int *marker_count, \
int *first, int *second)
{
	str[*first] = MARKER;
	str[*second] = MARKER;
	*marker_count += 2;
	*first = -1;
	*second = -1;
}

void	init_quote_struct(t_quotes *q)
{
	q->f_s = -1;
	q->s_s = -1;
	q->f_d = -1;
	q->s_d = -1;
}

void	replace_quotes(char *str, int *marker_count, int i)
{
	t_quotes	q;
	int			in_expansion;

	init_quote_struct(&q);
	in_expansion = 0;
	while (str[++i])
	{
		if (str[i] == '\x02')
			in_expansion = !in_expansion;
		if (in_expansion)
			continue ;
		if (q.f_d == -1 && str[i] == '\"' && q.f_s == -1)
			q.f_d = i;
		else if (q.f_d != -1 && str[i] == '\"')
			q.s_d = i;
		else if (q.f_s == -1 && str[i] == '\'' && q.f_d == -1)
			q.f_s = i;
		else if (q.f_s != -1 && str[i] == '\'')
			q.s_s = i;
		if (q.f_s != -1 && q.s_s != -1)
			replace_and_reset(str, marker_count, &q.f_s, &q.s_s);
		else if (q.f_d != -1 && q.s_d != -1)
			replace_and_reset(str, marker_count, &q.f_d, &q.s_d);
	}
}

char	*remove_marker(t_mini *data, char *str, int marker_count, char marker)
{
	char	*new_string;
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (marker_count == 0)
		return (str);
	new_string = malloc(sizeof(char) * (ft_strlen(str) - marker_count) + 1);
	if (new_string == NULL)
		free_data_and_exit(data, 1);
	while (str[++i])
	{
		if (str[i] == marker)
			continue ;
		new_string[j] = str[i];
		j++;
	}
	free(str);
	new_string[j] = '\0';
	return (new_string);
}

void	clean_quotes(t_mini *data)
{
	int			i;
	t_parser	*tmp;
	int			marker_count;

	tmp = data->parser;
	while (tmp)
	{
		i = 0;
		while (tmp->commands && tmp->commands[i])
		{
			marker_count = 0;
			replace_quotes(tmp->commands[i], &marker_count, -1);
			if (marker_count > 0)
			{
				tmp->commands[i] = remove_marker(data, \
				tmp->commands[i], marker_count, MARKER);
			}
			i++;
		}
		clean_redirections(data, tmp, &marker_count);
		tmp = tmp->next;
	}
}
