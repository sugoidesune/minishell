/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lib_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:51:38 by tbatis            #+#    #+#             */
/*   Updated: 2025/02/24 20:08:59 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_list_append_new(t_list *list, void *content)
{
	t_list_el	*new;

	new = ft_new_list_el(content);
	if (new == NULL)
		return (NULL);
	ft_list_append(list, new);
	return (list);
}

void	ft_list_delete_el(t_list_el *list_el, void (*del)(void *))
{
	void	*content;

	if (list_el == NULL)
		return ;
	content = list_el->content;
	del(content);
	free(list_el);
}

void	ft_listclear(t_list *lst, void (*del)(void *))
{
	t_list_el	*current;
	t_list_el	*next_node;

	if (lst == NULL || lst->head == NULL)
		return ;
	current = lst->head;
	while (current)
	{
		next_node = current->next;
		del(current->content);
		free(current);
		current = next_node;
	}
	lst->head = NULL;
}

t_list	*ft_listmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_list;
	t_list_el	*current;
	void		*mapped_content;
	t_list_el	*new_node;

	if (lst == NULL || lst->head == NULL)
		return (NULL);
	current = lst->head;
	new_list = ft_new_list();
	while (new_list && current)
	{
		mapped_content = f(current->content);
		if (!mapped_content)
			return (ft_listclear(new_list, del), free(new_list), NULL);
		new_node = ft_new_list_el(mapped_content);
		if (!new_node)
		{
			del(mapped_content);
			return (ft_listclear(new_list, del), free(new_list), NULL);
		}
		ft_list_append(new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

t_list_el	*ft_list_at_index(t_list *list, int index)
{
	t_list_el	*current;
	int			i;

	if (!list || index < 0)
		return (NULL);
	current = list->head;
	i = 0;
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	return (current);
}
