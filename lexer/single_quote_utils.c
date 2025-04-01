/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:37:34 by mmusic            #+#    #+#             */
/*   Updated: 2025/04/01 18:42:35 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token *process_single_quotes(char **str, t_token *head, t_token **token)
{
    char *start = *str + 1; // Skip opening '
    char *quoted_str;

    while (**str && **str != '\'')
        (*str)++;
    if (!**str) {
        fprintf(stderr, "Error: Unclosed single quote\n");
        return head;
    }
    quoted_str = ft_strndup(start, *str - start);
    t_token *new = new_token(TOKEN_SINGLE_QUOTE, quoted_str);
    new->subtoken = new_subtoken(TOKEN_WORD, quoted_str);
    if (!head) {
        head = new;
        *token = head;
    } else {
        (*token)->next = new;
        *token = new;
    }
    free(quoted_str);
    return head;
}