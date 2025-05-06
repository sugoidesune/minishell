/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:54:06 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 17:38:52 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser	t_parser;

typedef struct s_parser
{
	char		**commands;
	int			builtin;
	char		*heredoc_name;
	char		*heredoc_delim;
	t_lexer		*redirections;
	t_parser	*next;
	t_parser	*prev;
}	t_parser;

void		parser(t_mini *data);
t_lexer		*store_commands(t_mini *data, t_lexer *tmp, t_parser **node);
t_lexer		*remove_pipe(t_mini *data, t_lexer *tmp);
t_lexer		*handle_redirections(t_mini *data, t_lexer *lex_node, \
t_parser *node);
t_lexer		*store_redirection(t_lexer **token, t_parser **pars_node, \
t_mini *data);
void		add_node_parser(t_parser *node, t_parser **parser_list);
t_parser	*new_node_parser(char *cmd);
void		free_node_parser(t_parser **node);
int			count_nodes(t_parser *parser_list);
int			count_commands(t_mini *data, t_lexer *tmp);
t_lexer		*error_check(t_mini *data);
int			unexpected_token_error(t_mini *data, t_lexer *node);
int			check_builtin(char *cmd);
t_lexer		*get_lexer_head(t_lexer *node);

#endif
