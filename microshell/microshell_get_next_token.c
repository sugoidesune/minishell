#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>  // Add this line
#include <stdbool.h>

// Function to capture user input
char *capture_input(void) {
    char *input = readline("microshell> "); // Get input with a prompt
    if (input == NULL) {                    // Ctrl+D returns NULL
        write(1, "\n", 1);                  // Newline for clean exit
        exit(0);                            // Exit the shell
    }
    return input;
}

bool string_equals(char *str1, char *str2) {
    int i;

    i = 0;
    if(str1 == NULL || str2 == NULL) {
        return false; // One of the strings is NULL
    }
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false; // Strings are not equal
        }
        i++;
    }
    if(str1[i] != '\0' || str2[i] != '\0') {
        return false; // Strings are not equal
    }
    else
        return true;
}

char *get_next_token(char *str, char *delimiter) {
    static char *original = NULL;
    static char *current = NULL;
    char *token;
    char *result;

    if (str == NULL) {
        free(original);
        original = NULL;
        current = NULL;
        return NULL;
    }
    if (original == NULL || !string_equals(str, original)) {
        free(original);
        original = strdup(str);
        current = original;
    }
    token = strsep(&current, delimiter);
    if (token == NULL)
        return NULL;
    result = malloc(strlen(token) + 1);
    if (result == NULL) {
        perror("malloc");
        exit(1);
    }
    strcpy(result, token);
    return result;
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
        pid_t pid = 0;              // Create a child process
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