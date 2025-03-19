/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:43:02 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/19 17:12:07 by mmusic           ###   ########.fr       */
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

static void extract_quoted_content(char **str, char **quoted_str)
{
	char *start;

	(*str)++; // Skip the opening double quote
	start = *str;
	
	// Find closing double quote
	while (**str && **str != '"')
		(*str)++;
	
	if (!**str) // If no closing quote is found
	{
		fprintf(stderr, "Error: Unclosed double quote\n");
		*quoted_str = NULL;
		return;
	}
	
	*quoted_str = strndup(start, *str - start);
}

static void add_word_subtoken(char *quoted_str, size_t start, size_t end, 
							  t_subtoken **head, t_subtoken **current)
{
	char *content;

	if (end > start)
	{
		content = strndup(quoted_str + start, end - start);
		*head = add_subtoken_to_list(*head, current, TOKEN_WORD, content);
		free(content);
	}
}

static size_t process_variable_in_quotes(char *quoted_str, size_t i, 
										t_subtoken **head, t_subtoken **current)
{
	size_t word_start;
	char *content;

	word_start = i + 1; // Skip $
	i++;
	
	// Find end of variable name
	while (quoted_str[i] && ((quoted_str[i] >= 'a' && quoted_str[i] <= 'z') || 
		   (quoted_str[i] >= 'A' && quoted_str[i] <= 'Z') || 
		   (quoted_str[i] >= '0' && quoted_str[i] <= '9') || 
		   quoted_str[i] == '_'))
		i++;
	
	// Add variable as subtoken
	if (i > word_start)
	{
		content = strndup(quoted_str + word_start, i - word_start);
		*head = add_subtoken_to_list(*head, current, TOKEN_VARIABLE, content);
		free(content);
	}
	else
	{
		// Handle lone $ in quotes
		*head = add_subtoken_to_list(*head, current, TOKEN_WORD, "$");
	}
	
	return i;
}

static t_subtoken *parse_quoted_content(char *quoted_str)
{
	t_subtoken *head = NULL;
	t_subtoken *current = NULL;
	size_t i = 0, word_start = 0;

	while (quoted_str[i])
	{
		if (quoted_str[i] == '$')
		{
			add_word_subtoken(quoted_str, word_start, i, &head, &current);
			i = process_variable_in_quotes(quoted_str, i, &head, &current);
			word_start = i;
			continue;
		}
		i++;
	}
	
	// Add any remaining text after the last variable
	add_word_subtoken(quoted_str, word_start, i, &head, &current);
	
	return head;
}

t_token *process_double_quotes(char **str, t_token *head, t_token **token)
{
	char *quoted_str;
	t_token *new;
	t_subtoken *subtoken_head;
	
	extract_quoted_content(str, &quoted_str);
	if (!quoted_str)
		return head;
	new = new_token(TOKEN_DOUBLE_QUOTE, quoted_str);
	subtoken_head = parse_quoted_content(quoted_str);
	new->subtoken = subtoken_head;
	if (!head)
	{
		head = new;
		*token = head;
	}
	else
	{
		(*token)->next = new;
		*token = new;
	}
	free(quoted_str);
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
			head = process_double_quotes(&str, head, &token);
		else if(*str == '$')
			head = process_variable(&str, head, &token);
		else
			head = process_word(&str, head, &token);
		str++;
	}
	return (head);
}

static void print_token_info(t_token *token)
{
	t_subtoken *subtoken;
	
	printf("type: %d, value: '%s'\n", token->type, token->value);
	if (token->subtoken)
	{
		printf("  Contains subtokens:\n");
		subtoken = token->subtoken;
		while (subtoken)
		{
			printf("    subtype: %d, subvalue: '%s'\n", 
				subtoken->type, subtoken->value);
			subtoken = subtoken->next;
		}
	}
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
		print_token_info(token);
		token = token->next;
    }
	free_tokens(head);	
	return (0);
}