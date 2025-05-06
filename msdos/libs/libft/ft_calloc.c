/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:31:37 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/19 20:02:52 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char			*array;
	size_t					i;

	i = 0;
	array = malloc(num * size);
	if (!array)
		return (0);
	while (i < (num * size))
		array[i++] = 0;
	return ((void *)array);
}
