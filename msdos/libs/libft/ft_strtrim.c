/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:13:58 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/22 09:51:11 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	string_start(char const *s1, char const *set)
{
	int	start;
	int	i;
	int	stop;

	start = 0;
	while (s1[start])
	{
		stop = 1;
		i = 0;
		while (set[i])
		{
			if (s1[start] == set[i])
			{
				stop = 0;
				break ;
			}
			i++;
		}
		if (stop)
			break ;
		start++;
	}
	return (start);
}

int	string_end(char const *s1, char const *set)
{
	int	end;
	int	i;
	int	stop;

	end = ft_strlen(s1) - 1;
	while (end >= 0)
	{
		stop = 1;
		i = 0;
		while (set[i])
		{
			if (s1[end] == set[i])
			{
				stop = 0;
				break ;
			}
			i++;
		}
		if (stop)
			break ;
		end--;
	}
	return (end);
}

void	fill_string(char const *s1, char *new_str, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		new_str[i] = s1[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new_str;

	if (!set)
		return (0);
	if (!s1)
		return (ft_strdup(s1));
	start = string_start(s1, set);
	end = string_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	new_str = (char *)malloc((end - start + 1) + 1);
	if (new_str == 0)
		return (0);
	fill_string(s1, new_str, start, end);
	return (new_str);
}
