/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:07:55 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:07:58 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

t_env	*find_env_variable(t_env *env, const char *variable)
{
	t_env	*temp;
	char	*sinigual;
	char	*conigual;

	temp = env;
	sinigual = ft_strtrim(variable, "=");
	conigual = ft_strjoin(sinigual, "=");
	while (temp)
	{
		if (!ft_strcmp(temp->variable, sinigual))
		{
			free(conigual);
			free(sinigual);
			return (temp);
		}
		if (!ft_strcmp(temp->variable, conigual))
		{
			free(conigual);
			free(sinigual);
			return (temp);
		}
		temp = temp->next;
	}
	return (free(conigual), free(sinigual), NULL);
}

int	doublepointerlenght(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	print_export_variable(t_env *temp)
{
	if (ft_strchr(temp->variable, '=') && temp->content == NULL)
		printf("declare -x %s%s\n", temp->variable, "''");
	else if (temp->content == NULL)
		printf("declare -x %s\n", temp->variable);
	else
		printf("declare -x %s\"%s\"\n", temp->variable, temp->content);
}

int	ft_export(t_mini *data, t_parser *node)
{
	int			len;
	int			j;
	t_env		*export_cpy;
	char		**arg;
	t_content	content;

	j = 0;
	if (node->prev)
		return (0);
	arg = data->parser->commands;
	if (!arg || !data)
		return (1);
	len = doublepointerlenght(arg);
	export_cpy = export_list(data->env_list);
	content.variable = NULL;
	content.content = NULL;
	if (ft_strcmp("export", arg[0]) == 0)
	{
		if (len == 1)
			print_export_list(export_cpy);
		else
			j = process_export_variables(data, arg, len, &content);
	}
	free_env_list(export_cpy);
	return (j);
}
