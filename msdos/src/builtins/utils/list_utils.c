/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:12:35 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:12:38 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

void	add_last_node(t_env **env_cpy, t_env *new_node)
{
	t_env	*last_node;

	last_node = ft_last_node(*env_cpy);
	if (last_node)
	{
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	else
		*env_cpy = new_node;
}

t_env	*ft_last_node(t_env *env_cpy)
{
	t_env	*last;

	last = NULL;
	if (!env_cpy)
		return (NULL);
	while (env_cpy)
	{
		last = env_cpy;
		env_cpy = env_cpy->next;
	}
	return (last);
}

int	ft_export_error(void)
{
	ft_putstr_fd("export: -=: invalid option\n", 2);
	ft_putstr_fd("export:", 2);
	ft_putstr_fd(" usage: export [-fn] [name[=value] ...] or export -p\n", 2);
	return (1);
}

int	invalid_arg(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
