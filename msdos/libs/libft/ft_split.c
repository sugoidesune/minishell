/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 07:02:37 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/22 10:53:13 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	string_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	str_len(char const *str, char c, int i)
{
	int	len;

	len = 0;
	while (str[i] != c && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

static void	free_array(char **array, int j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**array;
	int		len;
	int		j;

	i = 0;
	j = -1;
	array = (char **)malloc((string_count(s, c) + 1) * sizeof(char *));
	if (!array)
		return (0);
	while (++j < string_count(s, c))
	{
		while (s[i] == c)
			i++;
		len = str_len(s, c, i);
		array[j] = ft_substr(s, i, len);
		if (!array[j])
		{
			free_array(array, j);
			return (0);
		}
		i = i + len;
	}
	array[j] = 0;
	return (array);
}
