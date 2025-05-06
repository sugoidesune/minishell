/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:37:42 by codespace         #+#    #+#             */
/*   Updated: 2024/12/19 20:05:36 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"
#include <limits.h>
#include <errno.h> 

int	ft_comands_len(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		i++;
	return (i);
}

int	check_number(char *number)
{
	int	i;

	i = 0;
	if (number[i] == '-')
		i++;
	while (number[i])
	{
		if (!ft_isdigit(number[i]))
			return (1);
		i++;
	}
	return (0);
}

static long long	ft_strtoll(const char *str)
{
	long long	result;
	int			sign;
	int			digit;

	result = 0;
	sign = 1;
	while (is_whitespace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			break ;
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (LLONG_MAX);
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

static long long	safe_atoi(char *str)
{
	long long	result;

	result = ft_strtoll(str);
	if (result == LLONG_MAX && errno == ERANGE)
		return (LLONG_MAX);
	return (result);
}

int	ft_exit(t_mini *data, t_parser *node)
{
	long long	exit_code;
	int			comands_len;

	if (node->prev)
		return (0);
	comands_len = ft_comands_len(data->parser->commands);
	if (comands_len > 2)
		return (write(2, "exit: too many arguments\n", 25), 1);
	if (comands_len == 2 && check_number(data->parser->commands[1]))
	{
		printf("exit: %s: %s", data->parser->commands[1], NUMERICERROR);
		free_data_and_exit(data, 2);
	}
	if (comands_len == 2)
	{
		exit_code = safe_atoi(data->parser->commands[1]);
		exit_code = length_2(exit_code, data);
		free_data_and_exit(data, (int)exit_code);
	}
	if (comands_len == 1)
	{
		printf("exit\n");
		free_data_and_exit(data, 0);
	}
	return (0);
}
