/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:18:17 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 20:05:10 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	printf_print_hex(const char c, int *chars_printed, va_list args)
{
	unsigned int	number;
	bool			print_capital;

	print_capital = (c == 'X');
	if (c == 'x' || c == 'X')
	{
		number = va_arg(args, unsigned int);
		*chars_printed += ft_putnbr_base(number, print_capital);
		return (true);
	}
	return (false);
}

bool	printf_print_pointer(const char c, int *chars_printed, va_list args)
{
	void				*pointer;
	unsigned long int	addr;

	if (c == 'p')
	{
		pointer = va_arg(args, void *);
		if (pointer == NULL)
		{
			*chars_printed += write(1, "(nil)", 5);
			return (true);
		}
		*chars_printed += write(1, "0x", 2);
		addr = (unsigned long int)pointer;
		*chars_printed += ft_putnbr_base((unsigned long int)(addr), false);
		return (true);
	}
	return (false);
}

bool	printers(const char c, int *chars_printed, va_list args)
{
	bool	has_printed;

	has_printed = !(printf_print_percent(c, chars_printed)
			|| printf_print_char(c, chars_printed, args)
			|| printf_print_string(c, chars_printed, args)
			|| printf_print_num(c, chars_printed, args)
			|| printf_print_unum(c, chars_printed, args)
			|| printf_print_hex(c, chars_printed, args)
			|| printf_print_pointer(c, chars_printed, args));
	return (has_printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		chars_printed;

	chars_printed = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (printers(*format, &chars_printed, args))
				return (-1);
		}
		else
			chars_printed += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (chars_printed);
}
