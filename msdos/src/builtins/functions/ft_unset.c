/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:08:47 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:08:49 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

static int	ft_free_from_env(t_env **head, t_env *env)
{
	if (!env)
		return (1);
	if (!env->prev)
		*head = env->next;
	else
		env->prev->next = env->next;
	if (env->next)
		env->next->prev = env->prev;
	free(env->variable);
	free(env->content);
	free(env);
	return (0);
}

size_t	ft_strnlen(const char *string, size_t max)
{
	size_t	len;

	len = 0;
	while (string[len] != '\0' && len < max)
		len++;
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	len = ft_strnlen(s, n);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

char	*ft_withoutequal(char *arg)
{
	char	*new_var;
	int		i;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	new_var = ft_strndup(arg, i);
	if (!new_var)
		return (NULL);
	return (new_var);
}

int	ft_unset(t_mini *data, t_parser *node)
{
	t_env	*env_node;
	t_env	*next_node;
	char	**args;
	int		i;

	env_node = data->env_list;
	args = data->parser->commands;
	if (node->prev || !args[1])
		return (0);
	while (env_node)
	{
		next_node = env_node->next;
		i = -1;
		while (args[++i])
		{
			if (ft_strncmp(env_node->variable, args[i], \
			ft_strlen(args[i])) == 0)
			{
				ft_free_from_env(&data->env_list, env_node);
				break ;
			}
		}
		env_node = next_node;
	}
	return (0);
}
