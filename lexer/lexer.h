/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:41:13 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/19 16:20:47 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <readline/readline.h>  // readline()
#include <readline/history.h>   // add_history()
#include <stdlib.h>             // malloc(), free(), getenv()
#include <unistd.h>             // write(), access()
#include <string.h>             // strerror()
#include <stdio.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,     // <
    TOKEN_REDIRECT_OUT,    // >
    TOKEN_HEREDOC,         // <<
    TOKEN_APPEND,          // >>
    TOKEN_SINGLE_QUOTE,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_VARIABLE
} t_token_type;

typedef struct s_subtoken {
    t_token_type type;
    char *value;
    struct s_subtoken *next;
} t_subtoken;

typedef struct s_token {
    t_token_type type;
    char *value;
    t_subtoken *subtoken;          
    struct s_token *next;  
} t_token;

// Utils
char *ft_strdup(char *value);
int ft_strlen(char *str);
char *strndup(const char *s, size_t n);

// Token utils
t_token *new_token(t_token_type type, char *value);
t_token *add_token_to_list(t_token *head, t_token **current, t_token_type type, char *value);
void free_tokens(t_token *head);

// Subtoken utils
t_subtoken *new_subtoken(t_token_type type, char *value);
t_subtoken *add_subtoken_to_list(t_subtoken *head, t_subtoken **current, t_token_type type, char *value);

// Lexer functions
t_token *lexer(char *input);
t_token *process_word(char **str, t_token *head, t_token **token);
t_token *process_variable(char **str, t_token *head, t_token **token);
t_token *process_double_quotes(char **str, t_token *head, t_token **token);

// Redirect utils
t_token *process_redirect_in(char **str, t_token *head, t_token **token);
t_token *process_redirect_out(char **str, t_token *head, t_token **token);

#endif