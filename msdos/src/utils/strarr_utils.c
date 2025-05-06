/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:35:45 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 16:59:36 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	count_env_nodes(t_env *env_list)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_list_to_strarr(t_mini *data)
{
	t_env	*tmp;
	char	**env_strarr;
	int		i;

	i = 0;
	tmp = data->env_list;
	env_strarr = malloc(sizeof(char *) * (count_env_nodes(data->env_list) + 1));
	if (env_strarr == NULL)
		free_data_and_exit(data, 1);
	while (tmp)
	{
		if (tmp->content == NULL)
		{
			env_strarr[i] = ft_strdup(tmp->variable);
			i++;
			tmp = tmp->next;
			continue ;
		}
		env_strarr[i] = ft_strjoin(tmp->variable, tmp->content);
		i++;
		tmp = tmp->next;
	}
	env_strarr[i] = NULL;
	return (env_strarr);
}

size_t	strarr_len(char **strarr)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (strarr[i])
	{
		if (strarr[i][0] == '\0')
		{
			i++;
			continue ;
		}
		i++;
		len++;
	}
	return (len);
}

int	skip_empty_line(char **strarr, int *i)
{
	if (strarr[*i][0] == '\0')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

char	**strarr_cpy(char **strarr)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy = (char **)ft_calloc(strarr_len(strarr) + 1, sizeof(char *));
	if (cpy == NULL)
		exit (EXIT_FAILURE);
	while (strarr[i])
	{
		if (skip_empty_line(strarr, &i))
			continue ;
		cpy[j] = ft_strdup(strarr[i]);
		if (cpy[j] == NULL)
		{
			free_strarr(cpy);
			return (NULL);
		}
		i++;
		j++;
	}
	cpy[j] = NULL;
	return (cpy);
}
