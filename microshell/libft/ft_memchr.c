/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:16:37 by tbatis            #+#    #+#             */
/*   Updated: 2024/09/10 13:39:56 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	if (n < 1)
		return (NULL);
	while (n && *ptr != (unsigned char)c)
	{
		ptr++;
		n--;
	}
	if (n && *ptr == (unsigned char)c)
		return (ptr);
	return (NULL);
}
