/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:31:21 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 18:18:22 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

static char	*pathishome(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp("HOME=", env[i], 5) == 0)
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

static int	ft_error(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (1);
	}
	if (access(path, R_OK) == -1)
	{
		write(2, "Permission to read denied\n", 27);
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		write(2, "Permission to execute denied\n", 30);
		return (1);
	}
	return (0);
}

static int	cd_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

int	ft_cd(t_mini *data, t_parser *node)
{
	char	*path;
	int		length;

	length = doublepointerlenght(data->parser->commands);
	path = NULL;
	if (node->prev)
		return (0);
	if (length > 2)
		return (cd_error("cd: too many arguments\n"));
	if (data->parser->commands && data->parser->commands[1])
		path = data->parser->commands[1];
	if (data->parser->commands && !data->parser->commands[1])
		path = pathishome(data->env);
	if (!path)
		return (cd_error("HOME is not configured\n"));
	if (ft_error(path) == 1)
		return (1);
	if (chdir(path) != 0)
		return (cd_error("chdir failed\n"));
	return (0);
}
