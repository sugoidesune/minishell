/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:48:40 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/09 20:55:15 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function `ft_strjoin` concatenates two strings `s1` and `s2`
// and returns a new string that is the result of the concatenation.

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	i;

	i = 0;
	strjoin = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!strjoin)
		return (NULL);
	while (s1[i])
	{
		*strjoin = s1[i];
		strjoin++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		*strjoin = s2[i];
		strjoin++;
		i++;
	}
	*strjoin = '\0';
	return (strjoin - ft_strlen(s1) - ft_strlen(s2));
}
