/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:11:58 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/05 22:07:06 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro.h"

int	count_commands(t_list *commands)
{
	t_list_el	*current;
	int			count;

	current = commands->head;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
