/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:05:43 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/19 20:01:05 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (new == 0 || lst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new;
}
