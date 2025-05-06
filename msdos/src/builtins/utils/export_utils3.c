/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:10:34 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 19:10:36 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	check_numeric_syntax(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isdigit(arg[i]))
			break ;
		i++;
	}
	if (i > 0 && arg[i] == '\0')
		return (invalid_arg(arg));
	return (0);
}

int	check_dash_and_equals_syntax(char *arg)
{
	int	i;

	i = 0;
	while (arg[i++])
	{
		if (arg[i] == '-' && ft_strchr(arg, '=') != NULL)
		{
			if (arg[i + 1] == '=')
			{
				invalid_arg(arg);
				return (1);
			}
			else
				return (ft_export_error());
		}
	}
	return (0);
}

int	check_identifier_syntax(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (invalid_arg(arg));
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (invalid_arg(arg));
		i++;
	}
	return (0);
}

int	ft_sintax(char *arg)
{
	if (check_numeric_syntax(arg))
		return (1);
	if (check_dash_and_equals_syntax(arg))
		return (1);
	if (check_identifier_syntax(arg))
		return (1);
	return (0);
}

void	print_export_list(t_env *export_cpy)
{
	t_env	*temp;

	temp = export_cpy;
	while (temp)
	{
		print_export_variable(temp);
		temp = temp->next;
	}
}
