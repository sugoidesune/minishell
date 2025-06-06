/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lib_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:51:38 by tbatis            #+#    #+#             */
/*   Updated: 2025/02/20 19:57:44 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	ft_listsize(t_list *list)
{
	int			count;
	t_list_el	*list_element;

	if (!list || !list->head)
		return (0);
	count = 0;
	list_element = list->head;
	while (list_element)
	{
		count++;
		list_element = list_element->next;
	}
	return (count);
}

t_list_el	*ft_new_list_el(void *content)
{
	t_list_el	*new_el;

	new_el = (t_list_el *)malloc(sizeof(t_list_el));
	if (!new_el)
		return (NULL);
	(*new_el).content = content;
	(*new_el).next = NULL;
	(*new_el).previous = NULL;
	return (new_el);
}

t_list_el	*ft_listlast(t_list *lst)
{
	t_list_el	*list_element;

	if (lst == NULL || lst->head == NULL)
		return (NULL);
	list_element = lst->head;
	while (list_element->next)
	{
		list_element = list_element->next;
	}
	return (list_element);
}

t_list_el	*ft_listfirst(t_list *lst)
{
	t_list_el	*list_element;

	if (lst == NULL || lst->head == NULL)
		return (NULL);
	list_element = lst->head;
	while (list_element->previous)
	{
		list_element = list_element->previous;
	}
	return (list_element);
}

void	ft_listiter(t_list *lst, void (*f)(void *))
{
	t_list_el	*current;

	if (lst == NULL || lst->head == NULL)
		return ;
	current = lst->head;
	while (current)
	{
		f((*current).content);
		current = (*current).next;
	}
}
