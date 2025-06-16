/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:35:43 by tbatis            #+#    #+#             */
/*   Updated: 2025/03/05 17:14:21 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	printf_print_percent(const char c, int *chars_printed)
{
	if (c == '%')
	{
		*chars_printed += write(1, "%", 1);
		return (true);
	}
	return (false);
}

bool	printf_print_char(const char c, int *chars_printed, va_list args)
{
	char	character;

	if (c == 'c')
	{
		character = (char)va_arg(args, int);
		*chars_printed += write(1, &character, 1);
		return (true);
	}
	return (false);
}

bool	printf_print_string(const char c, int *chars_printed, va_list args)
{
	char	*string;

	if (c == 's')
	{
		string = va_arg(args, char *);
		if (string == NULL)
		{
			*chars_printed += write(1, "(null)", 6);
			return (true);
		}
		*chars_printed += write(1, string, ft_strlen(string));
		return (true);
	}
	return (false);
}
