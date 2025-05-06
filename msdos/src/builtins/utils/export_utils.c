/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:11:15 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:11:17 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

t_env	*export_list(t_env *original)
{
	t_env	*copy;
	t_env	*current;

	current = original;
	copy = NULL;
	while (current)
	{
		fill_env_list(&copy, current->variable, current->content);
		current = current->next;
	}
	bubble_sort_env_list(&copy);
	return (copy);
}

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_variable;
	char	*temp_content;

	temp_content = a->content;
	temp_variable = a->variable;
	a->variable = b->variable;
	a->content = b->content;
	b->variable = temp_variable;
	b->content = temp_content;
}

void	bubble_sort_env_list(t_env **head)
{
	t_env	*current;
	t_env	*last;
	int		swapped;

	swapped = 1;
	last = NULL;
	if (!head || !*head)
		return ;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current->next != last)
		{
			if (strcmp(current->variable, current->next->variable) > 0)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}
