/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:30:00 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/19 17:16:25 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_subtoken *new_subtoken(t_token_type type, char *value)
{
    t_subtoken *subtoken;

    subtoken = malloc(sizeof(t_subtoken));
    if (!subtoken)
    {
        perror("malloc");
        exit(1);
    }
    subtoken->type = type;
    subtoken->value = ft_strdup(value);
    subtoken->next = NULL;
    return (subtoken);
}

t_subtoken *add_subtoken_to_list(t_subtoken *head, t_subtoken **current, t_token_type type, char *value)
{
    t_subtoken *new;

    new = new_subtoken(type, value);
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

void free_subtokens(t_subtoken *head)
{
    t_subtoken *temp;
    t_subtoken *next;

    temp = head;
    while (temp)
    {
        next = temp->next;
        free(temp->value);
        free(temp);
        temp = next;
    }
}
