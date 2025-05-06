/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:19:21 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/22 12:05:41 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;
	unsigned int	j;
	unsigned int	actual_len;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	actual_len = ft_strlen(s + start);
	if (len > actual_len)
		len = actual_len;
	i = start;
	substr = (char *)malloc(len + 1);
	if (substr == 0)
		return (0);
	j = 0;
	while (i < start + len && s[i])
	{
		substr[j++] = s[i++];
	}
	substr[j] = '\0';
	return (substr);
}
