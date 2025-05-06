/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:09:38 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:09:42 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

char	*mark_cont(char *content);

int	update_env_variable(t_mini *data, const char *value, const char *prefix)
{
	char	*new_entry;
	char	**new_commands;
	int		i;

	new_entry = ft_strjoin(prefix, value);
	if (!new_entry)
		return (-1);
	new_commands = malloc(3 * sizeof(char *));
	if (!new_commands)
		return (free(new_entry), -1);
	new_commands[0] = "export";
	new_commands[1] = new_entry;
	new_commands[2] = NULL;
	if (data->parser->commands)
	{
		i = 0;
		while (data->parser->commands[i])
			free(data->parser->commands[i++]);
		free(data->parser->commands);
	}
	data->parser->commands = new_commands;
	ft_export(data, data->parser);
	return (free(new_entry), 0);
}

t_env	*env_list(char **env)
{
	int			i;
	char		*variable;
	t_content	content;
	t_env		*env_cpy;

	content.variable = NULL;
	content.content = NULL;
	env_cpy = NULL;
	i = 0;
	while (env && env[i])
	{
		variable = env[i];
		if (separate_varcont(variable, &content))
		{
			free_env_list(env_cpy);
			free_t_content(&content);
			return (NULL);
		}
		fill_env_list(&env_cpy, content.variable, content.content);
		free_t_content(&content);
		i++;
	}
	return (env_cpy);
}

int	separate_varcont(char *line, t_content *content)
{
	char	*equals_sign;

	equals_sign = ft_strchr(line, '=');
	content->has_equal = (equals_sign != NULL);
	if (equals_sign)
		content->variable = ft_strndup(line, (equals_sign - line) + 1);
	else
		content->variable = ft_strdup(line);
	if (!content->variable)
		return (1);
	if (equals_sign && *(equals_sign + 1) != '\0')
	{
		content->content = ft_strdup(equals_sign + 1);
		if (!content->content)
			return (free(content->variable), 1);
	}
	else
		content->content = NULL;
	return (0);
}

char	*mark_cont(char *content)
{
	char	*mark;
	int		i;

	i = 0;
	mark = ft_strdup(content);
	while (mark[i])
	{
		if (mark[i] == '\x05')
			mark[i] = ' ';
		i++;
	}
	return (mark);
}

void	fill_env_list(t_env **env_cpy, const char *variable,
		const char *content)
{
	t_env	*new_node;

	if (!env_cpy)
		return ;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		write(2, "error", 6);
		exit(1);
	}
	new_node->variable = ft_strdup(variable);
	if (content)
		new_node->content = mark_cont((char *)content);
	else
		new_node->content = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	add_last_node(env_cpy, new_node);
}
