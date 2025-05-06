/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:10:23 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:10:26 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	ft_sintax(char *arg);

int	process_export_variables(t_mini *data, char **arg,
		int len, t_content *content)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (i < len)
	{
		j = ft_sintax(arg[i]);
		if (j == 0)
			process_single_export_variable(data, arg, i, content);
		i++;
	}
	return (j);
}

void	process_single_export_variable(t_mini *data, char **arg,
		int i, t_content *content)
{
	t_env	*existing;

	if (separate_varcont(arg[i], content) == 0)
	{
		existing = find_env_variable(data->env_list, content->variable);
		if (!existing)
		{
			add_new_variable(data, content);
			free_t_content(content);
		}
		else
			update_existing_variable(existing, content);
	}
}

void	add_new_variable(t_mini *data, t_content *content)
{
	if (content->has_equal == 1)
		fill_env_list(&data->env_list, content->variable, content->content);
	else
		fill_env_list(&data->env_list, content->variable, NULL);
}

void	update_existing_variable(t_env *existing, t_content *content)
{
	char	*aux;

	aux = ft_strdup(existing->variable);
	if (!ft_strchr(existing->variable, '=') && content->has_equal == 1)
	{
		free(existing->variable);
		existing->variable = ft_strjoin(aux, "=");
	}
	if (content->has_equal == 1)
	{
		if (!content->content)
		{
			free(existing->content);
			existing->content = ft_strdup("");
		}
		else
		{
			free(existing->content);
			existing->content = mark_cont(content->content);
			free(content->content);
		}
	}
	free(aux);
	free(content->variable);
}
