/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:43:29 by tbatis            #+#    #+#             */
/*   Updated: 2024/09/10 16:20:42 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}

/*
char	ft_tupperware(unsigned int i, char c)
{
	printf("index: %d char: %c\n", i, c);
	return (c - 32);
}
int	main(void)
{
	printf("%s", ft_strmapi("hello", ft_tupperware));
} */
