/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:41:13 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/17 20:09:12 by mmusic           ###   ########.fr       */
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

typedef struct s_token {
    t_token_type type;
    char *value;          
    struct s_token *next;  
} t_token;

// Utils
char *ft_strdup(char *value);
int ft_strlen(char *str);

// Token utils
t_token *new_token(t_token_type type, char *value);

#endif