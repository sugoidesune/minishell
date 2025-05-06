/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:12:49 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/29 13:36:04 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"
#include <dirent.h>

void	remove_heredoc(void)
{
	struct dirent	*entry;
	DIR				*dp;
	char			filepath[1024];

	dp = opendir(".");
	if (dp == NULL)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (strncmp(entry->d_name, "heredoc_n.", 10) == 0)
		{
			ft_strcpy(filepath, "./");
			ft_strcat(filepath, entry->d_name);
			unlink(filepath);
		}
		entry = readdir(dp);
	}
	closedir(dp);
}

int	check_fd(int fd, int type, char *str)
{
	int	std_in_out;

	if (type == REDIR_IN || type == HERE_DOC)
		std_in_out = STDIN_FILENO;
	else
		std_in_out = STDOUT_FILENO;
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, std_in_out) < 0)
	{
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	dispatch_redirections(t_mini *data, t_lexer *redirection, t_parser *cmd)
{
	int	fd;

	if (redirection->type == REDIR_IN)
		fd = open(redirection->token, O_RDONLY);
	if (redirection->type == HERE_DOC)
		fd = open(cmd->heredoc_name, O_RDONLY);
	if (redirection->type == REDIR_OUT)
		fd = open(redirection->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (redirection->type == APPEND)
		fd = open(redirection->token, O_CREAT | O_RDWR | O_APPEND, 0644);
	data->in_fd = fd;
	return (check_fd(fd, redirection->type, redirection->token));
}

int	redirections(t_mini *data, t_parser *cmd)
{
	t_lexer	*redirection;

	redirection = cmd->redirections;
	if (!redirection)
		return (EXIT_SUCCESS);
	while (redirection)
	{
		if (dispatch_redirections(data, redirection, cmd))
			return (EXIT_FAILURE);
		redirection = redirection->next;
	}
	return (EXIT_SUCCESS);
}
