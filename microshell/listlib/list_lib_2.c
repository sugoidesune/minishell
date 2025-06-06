/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lib_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:51:38 by tbatis            #+#    #+#             */
/*   Updated: 2025/02/21 00:14:55 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_new_list(void)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	return (new_list);
}

t_list	*ft_list_from_el(t_list_el *list_element)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->head = list_element;
	return (new_list);
}

t_list	*ft_list_append(t_list *list, t_list_el *new_listelement)
{
	t_list_el	*last;
	t_list		*new_list;

	if (list == NULL)
	{
		new_list = ft_new_list();
		if (!new_list)
			return (NULL);
		new_list->head = new_listelement;
		return (new_list);
	}
	if (list->head == NULL)
	{
		list->head = new_listelement;
		return (list);
	}
	last = ft_listlast(list);
	last->next = new_listelement;
	new_listelement->previous = last;
	new_listelement->next = NULL;
	return (list);
}

t_list	*ft_list_prepend(t_list *list, t_list_el *new_listelement)
{
	t_list_el	*head;
	t_list		*new_list;

	head = list->head;
	if (list == NULL)
	{
		new_list = ft_new_list();
		if (!new_list)
			return (NULL);
		new_list->head = new_listelement;
		return (new_list);
	}
	if (head == new_listelement)
		return (list);
	if (head == NULL)
	{
		list->head = new_listelement;
		return (list);
	}
	new_listelement->next = head;
	new_listelement->previous = NULL;
	head->previous = new_listelement;
	list->head = new_listelement;
	return (list);
}

t_list	*ft_list_prepend_new(t_list *list, void *content)
{
	t_list_el	*new;

	new = ft_new_list_el(content);
	if (new == NULL)
		return (NULL);
	ft_list_prepend(list, new);
	return (list);
}
