Okay, here is a breakdown of the 42 Minishell program's architecture based on the provided files and callgraph.

## Minishell Architecture Overview

This program implements a basic Unix shell. Its core functionality revolves around a loop that reads user input, parses it into commands, expands variables and handles quotes, executes the commands (handling builtins, external programs, pipes, and redirections), and then waits for the next input.

The main phases are:

1.  **Initialization:** Setting up the shell environment, signal handling, and initial data structures.
2.  **Read-Execute Loop:** The main loop that reads input, processes it, and executes commands.
3.  **Lexing:** Breaking the raw input string into meaningful tokens (words, operators).
4.  **Parsing:** Organizing the tokens into a structured representation of commands and their relationships (e.g., pipes).
5.  **Expansion:** Handling variable expansion (like `$PATH` or `$?`), quote removal, and other substitutions.
6.  **Execution:** Running the commands, which involves handling built-in commands, finding and running external programs, setting up pipes, and managing input/output redirections.
7.  **Cleanup:** Freeing allocated memory after each command execution cycle.

The central data structure is `t_mini`, which holds the state of the shell, including the environment variables, the current input line, the token list (lexer output), the command list (parser output), process IDs, and other relevant information.

## Detailed Breakdown

1.  **Initialization (`main`, `init_data`, `env_list`, `set_pwd`, `init_signals`)**
    *   The `main` function starts the program.
    *   `init_data` is called to set up the initial state within the `t_mini` struct.
        *   It copies the environment variables passed to the program using `strarr_cpy`.
        *   It creates a linked list representation of the environment (`t_env`) using `env_list` for easier manipulation (e.g., for `export`, `unset`). `separate_varcont` helps split `VAR=value` strings.
        *   `set_pwd` initializes the `PWD` and `OLDPWD` variables based on the environment or current working directory.
        *   `init_signals` sets up signal handlers (e.g., for `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\\)) using `sigaction` to define custom behavior like displaying a new prompt or ignoring the signal.

2.  **Main Loop (`mini_loop`)**
    *   This function contains the primary loop of the shell.
    *   It uses `readline()` to read a line of input from the user, providing line editing and history features.
    *   It performs preliminary checks:
        *   Handles empty input or EOF (Ctrl+D).
        *   Checks for unclosed quotes using `count_quotes`.
        *   Ignores lines containing only whitespace using `is_whitespace`.
    *   If the input is valid, it's added to the history using `add_history()`.
    *   It then calls the functions for lexing, parsing, expansion, and execution in sequence.
    *   `clear_data` is called at the beginning of each loop iteration to free memory allocated in the previous cycle (like lexer and parser lists).

3.  **Lexing (`read_token`, `store_token`, `store_word`, `new_node_lexer`, etc.)**
    *   `read_token` takes the raw input line from `data->line`.
    *   It iterates through the line, identifying different types of tokens:
        *   Words (commands, arguments, filenames)
        *   Operators (`|`, `<`, `>`, `<<`, `>>`)
        *   Whitespace (used as a delimiter)
    *   Functions like `store_word`, `store_left_brackets`, `store_right_brackets` handle the logic for identifying the boundaries of each token. Quote handling (`store_token_in_quotes`) ensures that spaces within quotes don't split a token.
    *   `new_node_lexer` creates a new node (`t_lexer`) for each token, storing the token string and its type (e.g., `WORD`, `PIPE`, `REDIR_IN`).
    *   `add_node_lexer` adds the new node to the `data->lexer` linked list.
    *   Error handling (`free_data_and_exit`) is present for allocation failures.

4.  **Parsing (`parser`, `store_commands`, `handle_redirections`, `new_node_parser`, etc.)**
    *   The `parser` function takes the flat list of tokens (`data->lexer`) and transforms it into a structured list of commands (`data->parser`).
    *   The `t_parser` struct represents a single simple command. It contains:
        *   `commands`: An array of strings (command and arguments).
        *   `redirections`: A linked list (`t_lexer`) of redirection tokens associated with this command.
        *   Pointers (`next`, `prev`) to link commands separated by pipes.
        *   Information about heredocs (`heredoc_name`, `heredoc_delim`).
        *   A flag indicating if the command is a builtin (`builtin`).
    *   It iterates through the lexer list.
    *   `store_commands` gathers consecutive `WORD` tokens into the `commands` array for the current parser node.
    *   `handle_redirections` processes redirection tokens (`<`, `>`, `<<`, `>>`) and their associated filenames/delimiters, moving them from the main lexer list to the `redirections` list within the current `t_parser` node using `store_redirection`. `delete_redirection_lexer` removes the processed redirection tokens from the original lexer list.
    *   When a `PIPE` token is encountered, the current `t_parser` node is considered complete, added to the `data->parser` list using `add_node_parser`, and a new `t_parser` node is created for the next command. The pipe token is removed using `remove_pipe`.
    *   `check_builtin` identifies if the command is a known built-in.
    *   Syntax error checking (`error_check`, `unexpected_token_error`) validates the token sequence (e.g., preventing `||` or `> >`).

5.  **Expansion (`expander`, `expand_string`, `env_expand`, `clean_quotes`, etc.)**
    *   The `expander` iterates through the `t_parser` list.
    *   For each command node, it processes the `commands` array and the `redirections` list.
    *   `expand_string` is the core function that handles:
        *   Variable Expansion: Replaces `$VAR` with its value from the environment list (`data->env_list`) or an empty string if not found. `env_expand` manages this, calling `expand_substring` and `expand_var`. Special handling exists for `$?` (exit status) via `handle_question_mark`.
        *   Quote Removal: Removes quotes (`'` and `"`) that are not themselves quoted, after expansion. `clean_quotes` and related functions (`replace_quotes`, `remove_marker`) manage this, often using temporary markers to protect characters during intermediate steps.
    *   Expansion rules differ based on quoting (single quotes prevent expansion, double quotes allow it).
    *   Expansion is also applied to redirection filenames/delimiters (`expand_redirections`). Special care is taken for heredoc delimiters where expansion might be suppressed.
    *   `clean_spaces`, `clean_markers`, and `clean_cmd` perform final cleanup on the strings after expansion and quote removal.

6.  **Execution (`executor`, `one_command`, `multiple_commands`, `execute_command`, `redirections`, `builtin`, `path_finder`, etc.)**
    *   `executor` is the entry point for execution. It determines if there's a single command or multiple commands connected by pipes (`count_nodes`).
    *   **Heredocs:** Before any command runs, `check_heredoc` (called via `signal_heredoc` or `one_command`) iterates through the commands. If a `HERE_DOC` redirection exists, `handle_heredoc` is called.
        *   `make_heredoc` reads input lines until the delimiter is found, performs expansion if needed (based on whether the delimiter was quoted), and writes the result to a temporary file. The filename is stored in `parser->heredoc_name`.
    *   **Single Command (`one_command`):**
        *   Checks if the command is a builtin that needs to run in the parent process (e.g., `cd`, `export`, `unset`, `exit`) using `builtin_in_parent`. If so, `call_builtin_function` executes it directly.
        *   Otherwise, it `fork`s a child process.
        *   **Child Process:** Calls `execute_command`.
        *   **Parent Process:** Waits for the child using `waitpid` and stores the exit status.
    *   **Multiple Commands (`multiple_commands`):**
        *   Iterates through the `t_parser` list.
        *   Uses `pipe()` to create pipes between commands.
        *   Uses `fork()` for each command (`make_process`).
        *   **Child Processes:**
            *   `redirect_in_out` uses `dup2()` to connect the process's stdin/stdout to the appropriate pipe ends or the original stdin/stdout for the first/last command. Closes unused pipe ends.
            *   Calls `execute_command`.
        *   **Parent Process:** Closes pipe ends after they've been duplicated by children. Stores child PIDs. After launching all children, `wait_for_processes` waits for all children using `waitpid` and gets the exit status of the last command.
    *   **`execute_command` (runs in child process for non-parent builtins):**
        *   `redirections` handles input/output redirection using `open()` and `dup2()`. `dispatch_redirections` performs the specific `open` and `dup2` calls based on the redirection type (`<`, `>`, `>>`, or heredoc using the temporary file). `check_fd` handles errors and performs the `dup2`.
        *   If the command is a builtin (even one not run in the parent), `call_builtin_function` executes it (e.g., `echo`, `pwd`, `env`). The child then `exit`s.
        *   If not a builtin, `path_finder` searches the `PATH` environment variable (using `find_path_string`, `ft_split`, `path_checker`) to find the full path of the executable. `access` is used to check existence and permissions.
        *   `env_list_to_strarr` converts the internal `t_env` list back to a `char **` array suitable for `execve`.
        *   `execve()` replaces the child process image with the command to be executed. Error handling (`path_error`) occurs if `execve` fails (e.g., command not found).
    *   **Builtins (`ft_cd`, `ft_echo`, etc.):** These functions implement the logic for built-in commands, interacting with the `t_mini` data structure (especially `data->env_list`) as needed. `ft_export` and `ft_unset` heavily rely on manipulating the `t_env` linked list. `ft_exit` terminates the shell.

7.  **Cleanup (`clear_data`, `free_lexer_list`, `free_parser_list`, `free_strarr`, `free_env_list`, `remove_heredoc`)**
    *   `clear_data` is called in `mini_loop` to release memory used by the lexer and parser lists for the previous command.
    *   Specific `free_*` functions traverse the linked lists or arrays and free individual nodes/strings and then the container structure.
    *   `free_data_and_exit` is a utility to free all major allocated data structures and exit the program, typically used on critical errors.
    *   `remove_heredoc` cleans up temporary heredoc files after execution.

8.  **Utilities (`utils.h`, str_utils.h, strarr_utils.h, libft)**
    *   These headers declare various helper functions:
        *   String manipulation (`ft_strcmp`, `ft_strcat`, `ft_strcpy`, `ft_strncpy`, `ft_strdup`, `ft_substr`, `ft_strjoin`, etc.).
        *   String array handling (`strarr_cpy`, `strarr_len`, `free_strarr`).
        *   Memory allocation (`malloc`, often wrapped or via libft's `ft_calloc`).
        *   General utilities (`free_data_and_exit`, `is_whitespace`).
        *   Functions from the `libft` library are used extensively.

This structure separates the concerns of input reading, tokenization, parsing, expansion, and execution, although the expansion phase involves modifying the parsed command structure. The use of linked lists for tokens, commands, and environment variables allows for dynamic handling of varying input lengths and command structures.