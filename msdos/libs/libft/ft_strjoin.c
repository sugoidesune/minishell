/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:42:25 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/19 20:01:40 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_str;
	size_t		size;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(size);
	if (new_str == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		new_str[i++] = s2[j];
		++j;
	}
	new_str[i] = '\0';
	return (new_str);
}
