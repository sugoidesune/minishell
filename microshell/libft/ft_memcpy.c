/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:16:15 by tbatis            #+#    #+#             */
/*   Updated: 2024/10/11 14:55:51 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	if (n == 0)
		return (dest);
	while (i > 0)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		i--;
		dest++;
		src++;
	}
	return (dest - n);
}
