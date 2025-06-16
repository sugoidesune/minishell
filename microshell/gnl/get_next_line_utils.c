/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:42:28 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/11 20:17:45 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

bool	hasnewline(char *string)
{
	if (string == NULL)
		return (false);
	while (string && *string)
	{
		if (*string == '\n')
		{
			return (true);
		}
		string++;
	}
	return (false);
}

bool	setnewlinetoendline(char *string)
{
	while (string && *string)
	{
		if (*string == '\n')
		{
			string++;
			*string = '\0';
			return (true);
		}
		string++;
	}
	return (false);
}

char	*getafternewline(char *string)
{
	char	*dup;

	while (string && *string)
	{
		if (*string == '\n')
		{
			string++;
			dup = ft_strdup(string);
			if (!dup)
				return (set_error(ERR_MALLOC));
			return (dup);
		}
		string++;
	}
	return (NULL);
}
