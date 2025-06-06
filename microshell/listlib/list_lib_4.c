/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lib_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:18:36 by tbatis            #+#    #+#             */
/*   Updated: 2025/02/24 19:47:07 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool	ft_swap_el_content(t_list_el *first, t_list_el *second)
{
	void	*temp;

	if (!first || !second)
		return (false);
	temp = first->content;
	first->content = second->content;
	second->content = temp;
	return (true);
}

t_list_el	*ft_detach_head(t_list *list)
{
	t_list_el	*head;
	t_list_el	*new_head;

	if (!list || !list->head)
		return (NULL);
	head = list->head;
	new_head = head->next;
	head->next = NULL;
	if (!new_head)
		list->head = NULL;
	if (new_head)
	{
		new_head->previous = NULL;
		list->head = new_head;
	}
	return (head);
}

t_list_el	*ft_detach_tail(t_list *list)
{
	t_list_el	*tail;
	t_list_el	*new_tail;

	if (!list || !list->head)
		return (NULL);
	tail = ft_listlast(list);
	new_tail = tail->previous;
	tail->previous = NULL;
	if (!new_tail)
		list->head = NULL;
	if (new_tail)
		new_tail->next = NULL;
	return (tail);
}

t_list	*array_to_list(long *array, int count, void *(*create_content)(long))
{
	t_list	*list;
	int		i;
	void	*content;

	list = ft_new_list();
	if (!list)
		return (NULL);
	i = 0;
	while (i < count)
	{
		content = create_content(array[i]);
		if (!content || (content && !ft_list_append_new(list, content)))
		{
			free(content);
			free_list(&list);
			return (NULL);
		}
		i++;
	}
	return (list);
}

void	free_list(t_list **lst)
{
	ft_listclear(*lst, free);
	free(*lst);
	*lst = NULL;
}
