/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:33:43 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/10 12:36:06 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		result;
	t_list	*node;

	node = lst;
	result = 0;
	while (node != NULL)
	{
		result++;
		node = node->next;
	}
	return (result);
}
