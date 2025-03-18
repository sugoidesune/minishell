/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:43:02 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/18 16:41:58 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_whitespace(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}

t_token	*process_word(char **str, t_token *head, t_token **token)
{
	char	*start;
	char	*word;

	start = *str;
	while (**str && **str != ' ' && **str != '\t' && **str != '|' 
		&& **str != '<' && **str != '>' && **str != '\'' && **str != '"'
		&& **str != '$')
		(*str)++;
	word = strndup(start, *str - start);
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
		var_name = strndup(start, *str - start);
		head = add_token_to_list(head, token, TOKEN_VARIABLE, var_name);
		free(var_name);
			head = add_token_to_list(head, token, TOKEN_WORD, "$");
    }
	(*str)--; // Move back one to account for the increment in the main loop
	return (head);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*token;
	char	*str;

	head = NULL;
	token = NULL;
	str = input;
	while (*str)
	{
		skip_whitespace(&str);
		if (!*str)
			break;
		if (*str == '|')
			head = add_token_to_list(head, &token, TOKEN_PIPE, "|");
		else if (*str == '<')
			head = process_redirect_in(&str, head, &token);
		else if (*str == '>')
			head = process_redirect_out(&str, head, &token);
		else if (*str == '\'')
			head = add_token_to_list(head, &token, TOKEN_SINGLE_QUOTE, "'");
		else if (*str == '"')
			head = add_token_to_list(head, &token, TOKEN_DOUBLE_QUOTE, "\"");
		else if(*str == '$')
			head = process_variable(&str, head, &token);
		else
			head = process_word(&str, head, &token);
		str++;
	}
	return (head);
}

int	main(int argc, char **argv)
{
	t_token	*token;
    t_token	*head;

    token = NULL;
    head = NULL;
    if (argc != 2)
    {
		printf("Usage: %s \"command\"\n", argv[0]);
		return (1);
	}
	head = lexer(argv[1]);
	token = head;
	while (token)
	{
		printf("type: %d, value: '%s'\n", token->type, token->value);
		token = token->next;
    }
	free_tokens(head);	
	return (0);
}