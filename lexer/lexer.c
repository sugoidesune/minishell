/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:43:02 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/17 20:17:01 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token *lexer(char *input)
{
    t_token *head;
    t_token *token;
    char *str;

    head = NULL;
    str = input;
    while (*str)
    {
        if (*str == '|')
        {
            if (!head)
            {
                head = new_token(TOKEN_PIPE, "|");
                token = head;
            }
            else
            {
                token->next = new_token(TOKEN_PIPE, "|");
                token = token->next;
            }
        }
        else if (*str == '<')
        {
            if (!head)
            {
                head = new_token(TOKEN_REDIRECT_IN, "<");
                token = head;
            }
            else
            {
                token->next = new_token(TOKEN_REDIRECT_IN, "<");
                token = token->next;
            }
        }
        else if (*str == '>')
        {
            if (*(str + 1) == '>')
            {
                if (!head)
                {
                    head = new_token(TOKEN_APPEND, ">>");
                    token = head;
                }
                else
                {
                    token->next = new_token(TOKEN_APPEND, ">>");
                    token = token->next;
                }
                str++;
            }
            else
            {
                if (!head)
                {
                    head = new_token(TOKEN_REDIRECT_OUT, ">");
                    token = head;
                }
                else
                {
                    token->next = new_token(TOKEN_REDIRECT_OUT, ">");
                    token = token->next;
                }
            }
        }
        else if (*str == '\'')
        {
            if (!head)
            {
                head = new_token(TOKEN_SINGLE_QUOTE, "'");
                token = head;
            }
            else
            {
                token->next = new_token(TOKEN_SINGLE_QUOTE, "'");
                token = token->next;
            }
        }
        else if (*str == '"')
        {
            if (!head)
            {
                head = new_token(TOKEN_DOUBLE_QUOTE, "\"");
                token = head;
            }
            else
            {
                token->next = new_token(TOKEN_DOUBLE_QUOTE, "\"");
                token = token->next;
            }
        }
        else
        {
            char *start = str;
            while (*str && *str != ' ' && *str != '|' && *str != '<' && *str != '>' && *str != '\'' && *str != '"')
                str++;
            char *word = strndup(start, str - start);
            if (!head)
            {
                head = new_token(TOKEN_WORD, word);
                token = head;
            }
            else
            {
                token->next = new_token(TOKEN_WORD, word);
                token = token->next;
            }
            free(word);
            str--;
        }
        str++;
    }
    return (head);
}

int main(int argc, char **argv)
{
    t_token *token;
    t_token *head;

    if (argc != 2)
    {
        printf("Usage: %s \"command\"\n", argv[0]);
        return (1);
    }
    head = lexer(argv[1]); // Changed to pass only the command string
    token = head;
    while (token)
    {
        printf("type: %d, value: %s\n", token->type, token->value);
        token = token->next;
    }
    //free_tokens(head);
    return (0);
}