#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>  // Add this line

// Function to capture user input
char *capture_input(void) {
    char *input = readline("microshell> "); // Get input with a prompt
    if (input == NULL) {                    // Ctrl+D returns NULL
        write(1, "\n", 1);                  // Newline for clean exit
        exit(0);                            // Exit the shell
    }
    return input;
}


// Function to parse input into command and argument
void parse_input(char *input, char **command, char **arg) {
    *command = strtok(input, " ");   // First token is the command
    *arg = strtok(NULL, " ");        // Second token is the argument
    // We assume exactly one argument and no extra tokens
}

// Function to execute the command
void execute_command(char *command, char *arg) {
    if (strcmp(command, "echo") == 0) {
        write(1, arg, strlen(arg));      // Print the argument
        write(1, "\n", 1);               // Add a newline
    } else if (strcmp(command, "mkdir") == 0) {
        pid_t pid = fork();              // Create a child process
        if (pid == 0) {                  // Child process
            execl("/bin/mkdir", "mkdir", arg, NULL); // Run mkdir
            exit(1);                     // Exit if exec fails
        } else {                         // Parent process
            wait(NULL);                  // Wait for child to finish
        }
    }
}

// Main loop
int main(void) {
    char *input;
    char *command;
    char *arg;

    while (1) {
        input = capture_input();           // Step 1: Get input
        parse_input(input, &command, &arg); // Step 2: Parse it
        if (command != NULL && arg != NULL) { // Step 3: Execute if valid
            execute_command(command, arg);
        }
        free(input);                       // Clean up input
    }
    return 0;
}