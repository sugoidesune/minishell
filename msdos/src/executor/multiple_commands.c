/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:21:51 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/29 13:26:06 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	redirect_in_out(t_mini **data, t_parser *cmd, int pipes_ends[2])
{
	if (cmd->prev)
	{
		if (dup2((*data)->in_fd, STDIN_FILENO) < 0)
			free_data_and_exit(*data, 1);
		close((*data)->in_fd);
	}
	close(pipes_ends[0]);
	if (cmd->next)
	{
		if (dup2(pipes_ends[1], STDOUT_FILENO) < 0)
			free_data_and_exit(*data, 1);
	}
}

void	make_process(t_mini **data, t_parser *cmd, int pipes_ends[2], int idx)
{
	(*data)->pids[idx] = fork();
	if ((*data)->pids[idx] < 0)
		free_data_and_exit(*data, 1);
	else if ((*data)->pids[idx] == 0)
	{
		redirect_in_out(data, cmd, pipes_ends);
		execute_command(*data, cmd);
	}
}

void	wait_for_processes(t_mini **data)
{
	int	child_status;
	int	i;

	i = 0;
	while (i < count_nodes((*data)->parser))
	{
		waitpid((*data)->pids[i], &child_status, 0);
		i++;
	}
	if (WIFEXITED(child_status))
		(*data)->exit_code = WEXITSTATUS(child_status);
	if (g_status != 0)
	{
		(*data)->exit_code = g_status;
		printf("\n");
	}
}

void	multiple_commands(t_mini *data)
{
	int			pipes_ends[2];
	t_parser	*cmd;
	int			pid_idx;

	pid_idx = 0;
	if (signal_heredoc(data))
		return ;
	cmd = data->parser;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipes_ends);
		make_process(&data, cmd, pipes_ends, pid_idx);
		close(pipes_ends[1]);
		if (cmd->prev)
			close(data->in_fd);
		data->in_fd = pipes_ends[0];
		cmd = cmd->next;
		pid_idx++;
	}
	wait_for_processes(&data);
}
