/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:20:19 by tbatis            #+#    #+#             */
/*   Updated: 2024/09/10 11:48:30 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*bad_chars;
	char		*trimmed_str;
	size_t		len;
	size_t		i;

	i = 0;
	bad_chars = set;
	while (*s1 && ft_strchr(bad_chars, *s1))
	{
		s1++;
	}
	len = ft_strlen(s1);
	while (len && len - 1 > 0 && ft_strchr(bad_chars, s1[len - 1]))
		len--;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	while (len > i)
	{
		trimmed_str[i] = s1[i];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
