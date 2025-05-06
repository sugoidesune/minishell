/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:07:07 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:07:11 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	ft_env(t_mini *data)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = data->env_list;
	if (data->parser->commands[1])
	{
		write(2, "too many arguments\n", 20);
		return (1);
	}
	if (!temp)
		return (1);
	while (temp)
	{
		if (ft_strchr(temp->variable, '='))
		{
			if (!temp->content)
				printf("%s\n", temp->variable);
			else
				printf("%s%s\n", temp->variable, temp->content);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}
