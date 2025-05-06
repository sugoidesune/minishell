/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:08:00 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 14:08:02 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	print_err_hd(char *delim)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document at last line delimited by end-of-file", 2);
	ft_putstr_fd(" (wanted '", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}

int	is_delim(char c)
{
	if (c == '.' || c == ',' || c == '=' || c == '#' \
	|| c == ':' || c == '%' || c == '/')
		return (1);
	return (0);
}

void	clean_redirections(t_mini *data, t_parser *tmp, int *marker_count)
{
	t_lexer	*redir;

	redir = tmp->redirections;
	while (redir)
	{
		if (redir->type != HERE_DOC)
		{
			*marker_count = 0;
			replace_quotes(redir->token, marker_count, -1);
			if (*marker_count > 0)
				redir->token = remove_marker(data, redir->token, \
				*marker_count, MARKER);
		}
		redir = redir->next;
	}
}

int	space_in_redirection(char *redir)
{
	int	i;
	int	in_single;
	int	in_double;

	in_double = 0;
	in_single = 0;
	i = 0;
	while (redir[i])
	{
		if (redir[i] == '\"')
			in_double = !in_double;
		if (redir[i] == '\'')
			in_single = !in_single;
		if (!in_single && !in_double && is_whitespace(redir[i]))
			return (1);
		i++;
	}
	return (0);
}

int	expand_redirections(t_mini *data, t_parser *node)
{
	t_lexer	*redir;

	redir = node->redirections;
	while (redir)
	{
		if (redir->type != HERE_DOC)
			expand_string(data, &redir->token);
		if (space_in_redirection(redir->token))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}
