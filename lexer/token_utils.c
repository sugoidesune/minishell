/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:57:49 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/18 14:40:31 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token *new_token(t_token_type type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
    {
        perror("malloc");
        exit(1);
    }
    token->type = type;
    token->value = ft_strdup(value);
    token->next = NULL;
    return (token);
}

t_token *add_token_to_list(t_token *head, t_token **current, t_token_type type, char *value)
{
    t_token *new;

    new = new_token(type, value);
    if (!head)
    {
        head = new;
        *current = head;
    }
    else
    {
        (*current)->next = new;
        *current = new;
    }
    return (head);
}

void free_tokens(t_token *head)
{
    t_token *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}