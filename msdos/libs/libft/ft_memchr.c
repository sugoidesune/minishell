/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:50:48 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/17 17:41:53 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;
	unsigned char	ch;

	ch = (unsigned char)c;
	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == ch)
			return ((void *)&s[i]);
		i++;
	}
	return (0);
}
