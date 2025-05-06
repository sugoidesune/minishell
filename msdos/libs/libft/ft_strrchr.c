/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:37:13 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/17 18:37:37 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*p;
	int				i;
	unsigned char	ch;

	i = 0;
	p = 0;
	ch = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			p = (char *)&str[i];
		i++;
	}
	if (ch == '\0')
		p = (char *)&str[i];
	return (p);
}
