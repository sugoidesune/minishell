/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:29:25 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/05 15:29:26 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	*error_store(void)
{
	static int	error_store = 0;

	return (&error_store);
}

int	error_code(void)
{
	return (*error_store());
}

bool	had_error(void)
{
	return (error_code() != 0);
}

void	*set_error(int error)
{
	*error_store() = error;
	return (NULL);
}
