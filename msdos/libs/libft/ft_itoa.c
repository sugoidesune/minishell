/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:25:31 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/22 09:46:01 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long nb)
{
	int	result;

	if (nb == 0)
		return (1);
	if (nb < 0)
		nb = nb * -1;
	result = 0;
	while (nb != 0)
	{
		result++;
		nb = nb / 10;
	}
	return (result);
}

static void	fill_str(char *str, int digits, long nb)
{
	int	i;

	if (nb < 0)
	{
		nb = nb * -1;
		str[0] = '-';
		digits++;
	}
	i = digits;
	str[i] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return ;
	}
	while (i > 0 && nb > 0)
	{
		str[--i] = (nb % 10) + 48;
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		sign;
	long	nb;

	nb = n;
	sign = 0;
	if (nb < 0)
		sign = 1;
	digits = count_digits(nb);
	str = (char *)malloc((digits + sign + 1) * sizeof(char));
	if (str == 0)
		return (0);
	fill_str(str, digits, nb);
	return (str);
}
/*#include <stdlib.h>
int main()
{

	int flag = 0;
	
	if (strcmp(ft_itoa(12345), "12345") != 0)
		flag = ft_error("encountered issue handling positive integer.");
	if (strcmp(ft_itoa(-12345), "-12345") != 0)
		flag = ft_error("encountered issue handlig negative integer.");
	if (strcmp(ft_itoa(0), "0") != 0)
		flag = ft_error("encountered issue handling zero.");
	char *rslt = ft_itoa((int)2147483648);
	printf("result -> %s\n", rslt);
	if (strcmp(ft_itoa(10000), "10000") != 0)
		flag = ft_error("encountered issue handling integer ending with zeros.");
	if (strcmp(ft_itoa(10042), "10042") != 0)
		flag = ft_error("encountered issue handling integer containing zeros.");
	if (strcmp(ft_itoa(-2147483648), "-2147483648") != 0)
		flag = ft_error("ecountered issue handling INT_MIN.");
	if (strcmp(ft_itoa(2147483647), "2147483647") != 0)
		flag = ft_error("ecountered issue handling INT_MAX.");

	if (flag == 0)
		ft_okay();
 return 0;
}*/
