/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:50:27 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/26 07:46:53 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;

	j = 0;
	dest_len = ft_strlen(dest);
	i = dest_len;
	if (dest_len >= size)
		return (size + ft_strlen(src));
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[j] != '\0')
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (dest_len + ft_strlen(src));
}
