/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 09:17:00 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/18 14:09:46 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	ch;

	ch = (unsigned char)value;
	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = ch;
		i++;
	}
	return (str);
}
