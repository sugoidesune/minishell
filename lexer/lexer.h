/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:41:13 by mmusic            #+#    #+#             */
/*   Updated: 2025/06/17 20:54:26 by tbatis           ###   ########.fr       */
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
#include "../listlib/list.h"  // t_list, t_list_el
// include for pid_t

#include <sys/types.h>         // pid_t

// ANSI color codes
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

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

typedef struct s_redirection {
    t_token_type type;         // e.g., TOKEN_REDIRECT_IN, TOKEN_HEREDOC
    char         *filename;    // The target file or heredoc delimiter
    t_list_el    *next;     // If you make a linked list of redirections
    t_list_el    *prev;
} t_redirection;

// Structure to represent a single simple command
typedef struct s_command {
    char          *command_name; // e.g., "ls", "cat", "grep" BUT STILL KEEP IT IN ARGS
    char          **args;         // Array of strings: command and its arguments (e.g., {"ls", "-l", NULL})
    t_list        *redirections;  // Linked list of t_redirection structs
    char          *heredoc_name; // If you handle heredocs by writing to temp files
    int command_index; // Index in the pipeline (if part of a pipeline) basically index of the count of pipes.
    bool to_be_piped;  // basically always true unless its the last command in the list
    pid_t pid; // this gets populated when forking the process
    struct s_command *next;       // For pipelines: next command
    struct s_command *prev;       // For pipelines: previous command (optional, but good for listlib)
} t_command;

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
int validate_quotes(char *input);

#endif