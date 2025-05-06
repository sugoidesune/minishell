/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:44:40 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/29 13:24:38 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	executor(t_mini *data);
void	one_command(t_mini *data);
void	execute_command(t_mini *data, t_parser *cmd);
void	check_heredoc(t_mini *data, t_parser *cmd);
void	handle_heredoc(t_mini *data, t_parser **cmd, t_lexer **heredoc);
char	*new_heredoc_name(void);
int		make_heredoc(t_mini *data, t_parser **cmd, char *delimiter);
void	handle_quotes_heredoc(t_parser **cmd, t_lexer **heredoc);
void	multiple_commands(t_mini *data);
void	wait_for_processes(t_mini **data);
void	update_in_fd(t_mini **data, t_parser *cmd, int pipes_ends[2]);
void	make_process(t_mini **data, t_parser *cmd, int pipes_ends[2], \
int pid_idx);
void	redirect_in_out(t_mini **data, t_parser *cmd, int pipes_ends[2]);
int		redirections(t_mini *data, t_parser *cmd);
int		dispatch_redirections(t_mini *data, t_lexer *redirection, \
t_parser *cmd);
int		check_fd(int fd, int type, char *str);
char	*path_finder(char *cmd, char **env);
char	*find_path_string(char **env);
char	*path_checker(char **all_path, char *cmd);
void	print_err_hd(char *delim);
int		heredoc_is_quoted(char *heredoc_token);
char	**make_commands_cpy(char **commands);
void	path_error(char **commands);

#endif
