/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:30:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/25 15:21:57 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void extract_quoted_content(char **str, char **quoted_str)
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
	
	*quoted_str = ft_strndup(start, *str - start);
}

void add_word_subtoken(char *quoted_str, size_t start, size_t end, 
                      t_subtoken **head, t_subtoken **current)
{
	char *content;

	if (end > start)
	{
		content = ft_strndup(quoted_str + start, end - start);
		*head = add_subtoken_to_list(*head, current, TOKEN_WORD, content);
		free(content);
	}
}

size_t process_variable_in_quotes(char *quoted_str, size_t i, 
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
		content = ft_strndup(quoted_str + word_start, i - word_start);
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

t_subtoken *parse_quoted_content(char *quoted_str)
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
