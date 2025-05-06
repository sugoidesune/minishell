/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:36:12 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 18:00:10 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	break_case(t_mini *data, char *line, t_parser **cmd)
{
	if (g_status == 130)
	{
		data->exit_code = g_status;
		free(line);
		return (1);
	}
	if (!line)
	{
		print_err_hd((*cmd)->heredoc_delim);
		return (1);
	}
	if (ft_strcmp(line, (*cmd)->heredoc_delim) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	make_heredoc(t_mini *data, t_parser **cmd, char *heredoc_token)
{
	char	*line;
	int		heredoc_fd;

	g_status = 0;
	heredoc_fd = open((*cmd)->heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (break_case(data, line, cmd))
			break ;
		if (!heredoc_is_quoted(heredoc_token))
			expand_string(data, &line);
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	close(heredoc_fd);
	return (0);
}

char	*new_heredoc_name(void)
{
	static int	hd_num = -1;
	char		*heredoc_name;
	char		*heredoc_num;

	hd_num++;
	heredoc_num = ft_itoa(hd_num);
	heredoc_name = ft_strjoin("heredoc_n.\x04", heredoc_num);
	free(heredoc_num);
	return (heredoc_name);
}

void	handle_heredoc(t_mini *data, t_parser **cmd, t_lexer **heredoc)
{
	int	marker_count;

	marker_count = 0;
	if ((*cmd)->heredoc_name)
		free((*cmd)->heredoc_name);
	(*cmd)->heredoc_name = new_heredoc_name();
	if ((*cmd)->heredoc_delim)
		free((*cmd)->heredoc_delim);
	(*cmd)->heredoc_delim = ft_strdup((*heredoc)->token);
	replace_quotes((*cmd)->heredoc_delim, &marker_count, 0);
	(*cmd)->heredoc_delim = remove_marker(data, \
	(*cmd)->heredoc_delim, marker_count, MARKER);
	make_heredoc(data, cmd, (*heredoc)->token);
}

void	check_heredoc(t_mini *data, t_parser *cmd)
{
	t_lexer	*redir_tmp;

	(void)data;
	redir_tmp = cmd->redirections;
	while (redir_tmp)
	{
		if (redir_tmp->type == HERE_DOC)
		{
			handle_heredoc(data, &cmd, &redir_tmp);
			if (g_status == 130)
				break ;
		}
		redir_tmp = redir_tmp->next;
	}
}
