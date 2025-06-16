/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minilib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:28 by tbatis            #+#    #+#             */
/*   Updated: 2025/02/21 02:22:21 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

void	decimal_to_hex(unsigned long int decimal, char hexa_number[200],
		char *radix)
{
	int	i;
	int	j;

	i = 200 - 1;
	j = 0;
	while (decimal != 0)
	{
		hexa_number[i--] = radix[decimal % ft_strlen(radix)];
		decimal = decimal / ft_strlen(radix);
		j++;
	}
	j = 200 - j;
	i = 0;
	while (j < 200)
	{
		hexa_number[i++] = hexa_number[j++];
	}
	hexa_number[i] = '\0';
}

int	ft_putnbr_base(unsigned long int nbr, bool capital)
{
	char	hexa_number[200];
	char	*base;
	int		write_count;

	write_count = 0;
	if (capital)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nbr == 0)
	{
		hexa_number[0] = base[nbr];
		return (write(1, hexa_number, 1));
	}
	decimal_to_hex(nbr, hexa_number, base);
	write_count += write(1, hexa_number,
			(long unsigned int)ft_strlen(hexa_number));
	return (write_count);
}
