/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:57:49 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/19 16:23:35 by mmusic           ###   ########.fr       */
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
    token->subtoken = NULL;
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

void free_tokens(t_token *head)
{
    t_token     *temp;
    t_subtoken  *subtemp;
    t_subtoken  *subtemp2;

    while (head)
    {
        temp = head;
        head = head->next;
        if(temp->subtoken)
        {
            subtemp = temp->subtoken;
            while(subtemp)
            {
                subtemp2 = subtemp;
                subtemp = subtemp->next;
                free(subtemp2->value);
                free(subtemp2);
            }
        }
        free(temp->value);
        free(temp);
    }
}