# Minishell

Minishell is a simplified implementation of the Unix shell, designed to demonstrate the fundamental concepts of a command-line interface.

## Features

Minishell is a basic shell that can execute commands, handle input/output redirection, and implement various shell features. Some of the key features include:

* Executing simple commands like `ls`, `cd`, `mkdir`, and `rm`
* Handling input/output redirection using operators like `<`, `>`, and `>>`
* Implementing pipes (`|`) to connect the output of one command to the input of another
* Managing environment variables like `PATH`, `HOME`, and `USER`
* Catching and handling signals like `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+Backslash)
* Implementing built-in commands like `echo`, `pwd`, `cd`, and `exit`

Minishell is designed to be a minimal, yet functional, implementation of a Unix shell. It provides a solid foundation for understanding the basics of a command-line interface and can be used as a starting point for more complex shell implementations.

## High-level overview of how it works:

1. **Lexical Analysis**: The input string is tokenized into individual tokens, such as commands, arguments, and operators.
2. **Syntax Analysis**: The tokens are parsed to construct an abstract syntax tree (AST) representation of the command.
3. **Execution**: The parsed command is executed, which may involve:
	* Forking processes to execute external commands
	* Handling signals and managing input/output streams
	* Implementing built-in commands and functions
4. **Error Handling**: Error handling mechanisms are implemented to report and manage errors that occur during command execution.
5. **Looping**: The shell continuously loops, reading input from the user and executing commands until the user decides to exit.
