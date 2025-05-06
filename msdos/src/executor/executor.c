/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:11:59 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/29 13:14:03 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"
#include <dirent.h>

int	is_a_directory(char *cmd)
{
	DIR	*dir;

	dir = NULL;
	if (cmd)
		dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		return (1);
	}
	closedir(dir);
	return (0);
}

char	**new_commands(t_parser *cmd)
{
	char	**tmp;
	char	**commands;

	tmp = cmd->commands;
	commands = make_commands_cpy(cmd->commands);
	cmd->commands = commands;
	free_strarr(tmp);
	return (commands);
}

void	execute_command(t_mini *data, t_parser *cmd)
{
	char	*path;
	char	**env;

	cmd->commands = new_commands(cmd);
	if ((!cmd->commands || !cmd->commands[0]) && !cmd->redirections)
		exit (EXIT_SUCCESS);
	if (cmd->commands && is_a_directory(cmd->commands[0]))
		exit (126);
	if (cmd->redirections && redirections(data, cmd) != EXIT_SUCCESS)
		exit (EXIT_FAILURE);
	if (cmd->builtin)
		exit (call_builtin_function(data, cmd));
	if ((!cmd->commands || !cmd->commands[0]))
		exit(EXIT_SUCCESS);
	env = env_list_to_strarr(data);
	path = path_finder(cmd->commands[0], env);
	if (path == NULL)
		path_error(cmd->commands);
	execve(path, cmd->commands, env);
	free_strarr(env);
	exit (EXIT_SUCCESS);
}

void	one_command(t_mini *data)
{
	int			child_status;
	int			pid;
	t_parser	*cmd;

	cmd = data->parser;
	if (builtin(data, cmd))
		return ;
	check_heredoc(data, data->parser);
	if (g_status != 0)
		return ;
	pid = fork();
	if (pid < 0)
		free_data_and_exit(data, 1);
	if (pid == 0)
		execute_command(data, data->parser);
	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		data->exit_code = WEXITSTATUS(child_status);
	if (g_status != 0)
	{
		data->exit_code = g_status;
		printf("\n");
	}
}

void	executor(t_mini *data)
{
	int		commands;

	g_status = 0;
	commands = count_nodes(data->parser);
	if (commands > 1)
	{
		data->pids = (int *)malloc(sizeof(int) * commands);
		if (data->pids == NULL)
			free_data_and_exit(data, 1);
		multiple_commands(data);
	}
	else
		one_command(data);
	remove_heredoc();
}
