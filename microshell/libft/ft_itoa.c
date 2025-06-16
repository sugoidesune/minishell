/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:20:25 by tbatis            #+#    #+#             */
/*   Updated: 2024/09/20 18:23:56 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	str[0] = '0';
	if (n == -2147483648)
		return (ft_strlcpy(str, "-2147483648", 12), str);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n)
	{
		str[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

/*
int	main(void)
{
	// printf() displays the string inside quotation
	// printf("%d", 10/ 10);
	printf("FULLSTR:%s\n", ft_itoa(123));
	printf("FULLSTR:%s\n", ft_itoa(-123)); //–2147483648
	printf("FULLSTR:%s\n", ft_itoa(-2147483648));
	printf("FULLSTR:%s\n", ft_itoa(0));
	printf("FULLSTR:%s\n", ft_itoa(10000));
	printf("FULLSTR:%s\n", ft_itoa(2147483647));
	return (0);
} */
