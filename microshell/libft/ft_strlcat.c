/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:35:07 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 18:54:55 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, const char *src, unsigned int nb)
{
	char	*dest_pointer;

	dest_pointer = dest;
	while (*dest)
	{
		dest++;
	}
	while (*src && nb--)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_pointer);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dest_len;
	unsigned int	src_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	ft_strncat(dst, src, size - dest_len - 1);
	return (dest_len + src_len);
}
