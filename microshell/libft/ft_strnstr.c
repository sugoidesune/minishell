/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:58:45 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 18:55:06 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (*big && j < len)
	{
		while (j < len && big[i] && little[i] && big[i] == little[i])
		{
			i++;
			j++;
		}
		if (little[i] == '\0')
			return ((char *)big);
		j = j - i;
		i = 0;
		big++;
		j++;
	}
	return (NULL);
}
