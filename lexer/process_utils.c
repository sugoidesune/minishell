/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:30:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/25 15:22:06 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*process_word(char **str, t_token *head, t_token **token)
{
	char	*start;
	char	*word;

	start = *str;
	while (**str && **str != ' ' && **str != '\t' && **str != '|' 
		&& **str != '<' && **str != '>' && **str != '\'' && **str != '"'
		&& **str != '$')
		(*str)++;
	word = ft_strndup(start, *str - start);
	head = add_token_to_list(head, token, TOKEN_WORD, word);
	free(word);
	(*str)--;
	return (head);
}

t_token	*process_variable(char **str, t_token *head, t_token **token)
{
	char	*start;
	char	*var_name;

	(*str)++; // Skip the $ character
	start = *str;

	// Variable name can contain alphanumeric characters and underscore
	while (**str && ((**str >= 'a' && **str <= 'z') || 
		   (**str >= 'A' && **str <= 'Z') || 
		   (**str >= '0' && **str <= '9') || 
		   **str == '_'))
		(*str)++;

	if (start == *str) // Handle lone $ or $ followed by non-variable character
	{
		head = add_token_to_list(head, token, TOKEN_WORD, "$");
	}
	else
	{
		var_name = ft_strndup(start, *str - start);
		head = add_token_to_list(head, token, TOKEN_VARIABLE, var_name);
		free(var_name);
		head = add_token_to_list(head, token, TOKEN_WORD, "$");
    }
	(*str)--; // Move back one to account for the increment in the main loop
	return (head);
}
