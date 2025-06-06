#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <stdbool.h>

#define MAX_ARGS 10

// Function to capture user input
char *capture_input(void) {
    char *input = readline("microshell> "); // Get input with a prompt
    if (input == NULL) {                    // Ctrl+D returns NULL
        write(1, "\n", 1);                  // Newline for clean exit
        exit(0);                            // Exit the shell
    }
    return input;
}

// Function to parse input into commands and arguments
void parse_input(char *input, char **args) {
    int i;
    char *token;
    
    i = 0;
    token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Null-terminate the array
}

// Function to check if command contains a pipe
bool has_pipe(char **args) {
    int i;
    
    i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            return true;
        }
        i++;
    }
    return false;
}

// Function to execute commands with pipe
void execute_piped_command(char **args) {
    int i;
    int j;
    int pipe_fd[2];
    pid_t pid1;
    pid_t pid2;
    char *cmd1[MAX_ARGS];
    char *cmd2[MAX_ARGS];
    
    // Find pipe position
    i = 0;
    while (args[i] != NULL && strcmp(args[i], "|") != 0) {
        i++;
    }
    
    // Split commands before and after pipe
    j = 0;
    while (j < i) {
        cmd1[j] = args[j];
        j++;
    }
    cmd1[j] = NULL;
    
    j = 0;
    while (args[i + j + 1] != NULL) {
        cmd2[j] = args[i + j + 1];
        j++;
    }
    cmd2[j] = NULL;
    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return;
    }
    
    pid1 = fork();
    if (pid1 == 0) {
        // Child 1 - writes to pipe
        close(pipe_fd[0]);  // Close read end
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        
        if (strcmp(cmd1[0], "cat") == 0) {
            execl("/bin/cat", "cat", cmd1[1], NULL);
        }
        exit(1);
    }
    
    pid2 = fork();
    if (pid2 == 0) {
        // Child 2 - reads from pipe
        close(pipe_fd[1]);  // Close write end
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        
        if (strcmp(cmd2[0], "rev") == 0) {
            execl("/usr/bin/rev", "rev", NULL);
        }
        exit(1);
    }
    
    // Parent
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// Function to execute the command
void execute_command(char **args) {
    pid_t pid;
    
    if (has_pipe(args)) {
        execute_piped_command(args);
        return;
    }
    
    if (strcmp(args[0], "echo") == 0) {
        if (args[1] != NULL) {
            write(1, args[1], strlen(args[1]));
            write(1, "\n", 1);
        }
    } else if (strcmp(args[0], "mkdir") == 0) {
        if (args[1] != NULL) {
            pid = fork();
            if (pid == 0) {
                execl("/bin/mkdir", "mkdir", args[1], NULL);
                exit(1);
            } else {
                wait(NULL);
            }
        }
    } else if (strcmp(args[0], "cat") == 0) {
        if (args[1] != NULL) {
            pid = fork();
            if (pid == 0) {
                execl("/bin/cat", "cat", args[1], NULL);
                exit(1);
            } else {
                wait(NULL);
            }
        }
    } else if (strcmp(args[0], "rev") == 0) {
        pid = fork();
        if (pid == 0) {
            execl("/usr/bin/rev", "rev", NULL);
            exit(1);
        } else {
            wait(NULL);
        }
    }
}

// Main loop
int main(void) {
    char *input;
    char *args[MAX_ARGS];
    
    while (1) {
        input = capture_input();
        parse_input(input, args);
        if (args[0] != NULL) {
            execute_command(args);
        }
        free(input);
    }
    return 0;
}