/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:21:40 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 21:07:53 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	is_there_flag(char **args)
{
	int	j;
	int	i;

	j = 1;
	while (args[j])
	{
		if (ft_strncmp(args[j], "-n", 2) == 0)
		{
			i = 2;
			while (args[j][i] == 'n')
				i++;
			if (args[j][i] == '\0')
				j++;
			else
				break ;
		}
		else
			break ;
	}
	return (j);
}

int	ft_echo(t_mini *data, t_parser *cmd)
{
	int		i;
	char	**args;

	(void)data;
	args = cmd->commands;
	i = 1;
	if (args[i] == NULL)
	{
		printf("\n");
		return (0);
	}
	i = is_there_flag(args);
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (is_there_flag(args) == 1)
		printf("\n");
	return (0);
}
