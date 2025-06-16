/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:43:43 by tbatis            #+#    #+#             */
/*   Updated: 2025/02/18 20:00:04 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_sign(char str)
{
	if (str == '+' || str == '-')
		return (1);
	return (0);
}

static int	parse_sign(char *str)
{
	int	sign;

	sign = 1;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			sign = -sign;
		}
		str++;
	}
	return (sign);
}

static long	iter_atoi(char *str)
{
	long	num;

	num = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		num = num * 10;
		num = num + (*str - 48);
		str++;
	}
	return (num);
}

int	ft_atoi(char *str)
{
	int	sign_int;
	int	raw_number;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign_int = parse_sign(str);
	while (is_sign(*str))
		str++;
	raw_number = (int)iter_atoi(str);
	return (raw_number * sign_int);
}

long	ft_atol(char *str)
{
	int		sign_int;
	long	raw_number;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign_int = parse_sign(str);
	while (is_sign(*str))
		str++;
	raw_number = iter_atoi(str);
	return (raw_number * sign_int);
}
