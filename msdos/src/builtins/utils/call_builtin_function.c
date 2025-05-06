/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin_function.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:23:37 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 14:38:27 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	builtin(t_mini *data, t_parser *cmd)
{
	char	**tmp;
	char	**commands;

	tmp = cmd->commands;
	if (cmd->builtin && builtin_in_parent(cmd->commands[0]))
	{
		commands = make_commands_cpy(cmd->commands);
		cmd->commands = commands;
		free_strarr(tmp);
		data->exit_code = call_builtin_function(data, cmd);
		return (1);
	}
	return (0);
}

int	builtin_in_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
	{
		return (1);
	}
	return (0);
}

int	call_builtin_function(t_mini *data, t_parser *cmd)
{
	if (!ft_strcmp(cmd->commands[0], "cd"))
		return (ft_cd(data, cmd));
	if (!ft_strcmp(cmd->commands[0], "echo"))
		return (ft_echo(data, cmd));
	if (!ft_strcmp(cmd->commands[0], "env"))
		return (ft_env(data));
	if (!ft_strcmp(cmd->commands[0], "exit"))
		ft_exit(data, cmd);
	if (!ft_strcmp(cmd->commands[0], "export"))
		return (ft_export(data, cmd));
	if (!ft_strcmp(cmd->commands[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->commands[0], "unset"))
		return (ft_unset(data, cmd));
	return (0);
}
