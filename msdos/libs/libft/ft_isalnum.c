/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 08:10:55 by rgiambon          #+#    #+#             */
/*   Updated: 2024/06/09 12:57:44 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int character)
{
	if ((character >= 65 && character <= 90)
		|| (character >= 97 && character <= 122)
		|| (character >= 48 && character <= 57))
		return (1);
	return (0);
}
