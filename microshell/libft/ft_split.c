/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:18:22 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 18:54:00 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
			count++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (count);
}

static char	*ft_strldup(const char *s1, int len)
{
	char	*dup;

	if (!s1)
		return (NULL);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}

void	free_ft_split_array(char **string_array)
{
	char	**original;

	if (!string_array)
		return ;
	original = string_array;
	while (*string_array)
	{
		free(*string_array);
		string_array++;
	}
	free(original);
}

char	**ft_splitter(char const *s, char c, int word_count)
{
	char	**result;
	int		word_len;
	int		i;

	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	result[word_count] = NULL;
	while (i < word_count)
	{
		word_len = 0;
		while (*s && *s == c)
			s++;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		result[i] = ft_strldup(s, word_len);
		if (!result[i])
			return (free_ft_split_array(result), NULL);
		s += word_len;
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	return (ft_splitter(s, c, word_count));
}
