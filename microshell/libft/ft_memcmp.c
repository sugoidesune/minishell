/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:16:27 by tbatis            #+#    #+#             */
/*   Updated: 2024/09/10 15:02:43 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*su1;
	unsigned char	*su2;

	su1 = (unsigned char *)s1;
	su2 = (unsigned char *)s2;
	while (n && (*su1 == *su2))
	{
		su1++;
		su2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*su1 - *su2);
}
