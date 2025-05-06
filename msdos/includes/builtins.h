/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:17 by codespace         #+#    #+#             */
/*   Updated: 2024/12/19 21:15:19 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define ERROR 1
# define NUMERICERROR "Too many arguments\n"

typedef struct s_env	t_env;

typedef struct s_content
{
	char	*variable;
	char	*content;
	int		has_equal;
}	t_content;

int			ft_cd(t_mini *data, t_parser *node);
int			ft_echo(t_mini *data, t_parser *cmd);
int			ft_pwd(void);
int			ft_env(t_mini *data);
int			ft_export(t_mini *data, t_parser *cmd);
int			ft_unset(t_mini *data, t_parser *node);
int			ft_exit(t_mini *data, t_parser *cmd);
void		bubble_sort_env_list(t_env **head);
t_env		*export_list(t_env *original);
int			call_builtin_function(t_mini *data, t_parser *cmd);
int			builtin_in_parent(char *cmd);
void		free_env_list(t_env *env);
int			separate_varcont(char *line, t_content *content);
void		fill_env_list(t_env **env_cpy, const char *variable, \
const char *content);
t_env		*env_list(char **env);
void		free_t_content(t_content *content);
int			builtin(t_mini *data, t_parser *cmd);
int			doublepointerlenght(char **line);
int			process_export_variables(t_mini *data, char **arg, int len, \
t_content *content);
void		print_export_list(t_env *export_cpy);
char		*ft_strndup(const char *s, size_t n);
void		add_last_node(t_env **env_cpy, t_env *new_node);
int			ft_export_error(void);
int			invalid_arg(char *arg);
void		print_export_variable(t_env *temp);
void		process_single_export_variable(t_mini *data, \
char **arg, int i, t_content *content);
t_env		*find_env_variable(t_env *env, const char *variable);
void		add_new_variable(t_mini *data, t_content *content);
void		update_existing_variable(t_env *existing, t_content *content);
t_env		*ft_last_node(t_env *env_cpy);
void		remove_heredoc(void);
char		*mark_cont(char *content);
long long	length_2(long long exit_code, t_mini *data);
#endif
