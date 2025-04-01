/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:41:13 by mmusic            #+#    #+#             */
/*   Updated: 2025/04/01 18:42:32 by mmusic           ###   ########.fr       */
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

// String utils (utils.c)
char *ft_strdup(char *value);
int ft_strlen(char *str);
char *ft_strndup(const char *s, size_t n);
void skip_whitespace(char **str);

// Token utils (token_utils.c)
t_token *new_token(t_token_type type, char *value);
t_token *add_token_to_list(t_token *head, t_token **current, t_token_type type, char *value);
void free_tokens(t_token *head);

// Subtoken utils (subtoken_utils.c)
t_subtoken *new_subtoken(t_token_type type, char *value);
t_subtoken *add_subtoken_to_list(t_subtoken *head, t_subtoken **current, t_token_type type, char *value);
void free_subtokens(t_subtoken *head);

// Double quote processing (double_quote_utils.c)
void extract_quoted_content(char **str, char **quoted_str);
void add_word_subtoken(char *quoted_str, size_t start, size_t end, t_subtoken **head, t_subtoken **current);
size_t process_variable_in_quotes(char *quoted_str, size_t i, t_subtoken **head, t_subtoken **current);
t_subtoken *parse_quoted_content(char *quoted_str);
t_token *process_double_quotes(char **str, t_token *head, t_token **token);

// Redirect utils (redirect_utils.c)
t_token *process_redirect_in(char **str, t_token *head, t_token **token);
t_token *process_redirect_out(char **str, t_token *head, t_token **token);

// Processing functions (process_utils.c)
t_token *process_word(char **str, t_token *head, t_token **token);
t_token *process_variable(char **str, t_token *head, t_token **token);

t_token *process_single_quotes(char **str, t_token *head, t_token **token);

// Lexer main function (lexer.c)
t_token *lexer(char *input);
void print_token_info(t_token *token);

#endif