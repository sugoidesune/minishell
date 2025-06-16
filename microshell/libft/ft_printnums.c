/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnums.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:03:17 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 16:40:31 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(unsigned int num)
{
	int	write_count;

	write_count = 0;
	if (num >= 10)
	{
		write_count += ft_putnbr(num / 10);
	}
	write_count += ft_putchar((char)(num % 10 + 48));
	return (write_count);
}

bool	printf_print_num(const char c, int *chars_printed, va_list args)
{
	int	number;

	if (c == 'i' || c == 'd')
	{
		number = va_arg(args, int);
		if (number == -2147483648)
		{
			*chars_printed += write(1, "-2147483648", 11);
			return (true);
		}
		if (number < 0)
		{
			*chars_printed += ft_putchar('-');
			number = -number;
		}
		*chars_printed += ft_putnbr(number);
		return (true);
	}
	return (false);
}

bool	printf_print_unum(const char c, int *chars_printed, va_list args)
{
	unsigned int	number;

	if (c == 'u')
	{
		number = va_arg(args, unsigned int);
		*chars_printed += ft_putnbr(number);
		return (true);
	}
	return (false);
}
