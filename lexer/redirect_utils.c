/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:00:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/18 14:40:23 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*process_redirect_in(char **str, t_token *head, t_token **token)
{
	if (*((*str) + 1) == '<')
	{
		head = add_token_to_list(head, token, TOKEN_HEREDOC, "<<");
		(*str)++;
	}
	else
		head = add_token_to_list(head, token, TOKEN_REDIRECT_IN, "<");
	return (head);
}

t_token	*process_redirect_out(char **str, t_token *head, t_token **token)
{
	if (*((*str) + 1) == '>')
	{
		head = add_token_to_list(head, token, TOKEN_APPEND, ">>");
		(*str)++;
	}
	else
		head = add_token_to_list(head, token, TOKEN_REDIRECT_OUT, ">");
	return (head);
}
