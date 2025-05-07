#include <stdio.h> // For printf (allowed)
#include <stdlib.h> // For getenv, malloc, free (allowed)
#include <string.h> // For ft_strtok, ft_strcpy, ft_strcat (assuming from libft)
#include <unistd.h> // For access (allowed)

// You would use your libft functions like ft_split, ft_strjoin, ft_strlen etc.
// For demonstration, this uses standard library functions where equivalents are obvious.

// Assuming ft_split is available from your libft
char **ft_split(char const *s, char c);
// Assuming ft_strjoin is available
char *ft_strjoin(char const *s1, char const *s2);
// Assuming ft_strlen is available
size_t ft_strlen(const char *s);
// Assuming ft_strcpy is available
char *ft_strcpy(char *dest, const char *src);
// Assuming ft_strcat is available
char *ft_strcat(char *dest, const char *src);


char *find_command_in_path(const char *command) {
    char *path_env;
    char *path_env_copy;
    char **paths;
    char *executable_path;
    int i;

    path_env = NULL;
    path_env_copy = NULL;
    paths = NULL;
    executable_path = NULL;
    i = 0;

    path_env = getenv("PATH");

    if (path_env == NULL) {
        // PATH not set, command can only be found if it's an absolute/relative path
        // or a builtin, which should be checked before this.
        return NULL;
    }
    printf("%s\n", path_env); // Debug print

    // Duplicate path_env because ft_split might modify it or work on a copy
    // Or ensure ft_split doesn't modify its input if it's from your libft
    // For simplicity, let's assume ft_split handles this or we make a copy
    // path_env_copy = ft_strdup(path_env); // if you have ft_strdup

    // paths = ft_split(path_env, ':'); // Use your libft's ft_split
    // For this example, let's manually iterate, as ft_split is complex
    // This is a simplified tokenization for ':'
    char *current_path_segment;
    char *path_env_mutable; // strtok modifies the string

    path_env_mutable = malloc(strlen(path_env) + 1);
    if (path_env_mutable == NULL) {
        perror("malloc");
        return NULL;
    }
    strcpy(path_env_mutable, path_env);

    current_path_segment = strtok(path_env_mutable, ":"); // strtok is not allowed, use your own tokenizer
                                                        // This is just for concept illustration

    while (current_path_segment != NULL) {
        // Construct full path: directory + "/" + command
        // char *full_path = ft_strjoin(current_path_segment, "/");
        // char *final_path = ft_strjoin(full_path, command);
        // free(full_path); // if ft_strjoin allocates new memory

        // Manual construction to adhere to allowed functions (conceptual)
        executable_path = malloc(strlen(current_path_segment) + strlen(command) + 2);
        if (executable_path == NULL) {
            // Handle malloc failure
            perror("malloc");
            // free(path_env_mutable); // Free the copy
            // free_split_paths(paths); // if paths were allocated by ft_split
            return NULL; // Or handle error appropriately
        }
        strcpy(executable_path, current_path_segment);
        strcat(executable_path, "/");
        strcat(executable_path, command);

        if (access(executable_path, X_OK) == 0) {
            // Found an executable command
            // free(path_env_mutable);
            // free_split_paths(paths); // if paths were allocated
            return executable_path; // Return the full path
        }
        free(executable_path);
        executable_path = NULL;

        current_path_segment = strtok(NULL, ":"); // strtok is not allowed
    }

    free(path_env_mutable);
    // free_split_paths(paths); // if paths were allocated

    return NULL; // Command not found in PATH
}

// Example usage (conceptual, main not part of minishell)

int main(int argc, char **argv) {
    char *cmd_to_find;
    char *found_path;

    cmd_to_find = NULL;
    found_path = NULL;

    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }
    cmd_to_find = argv[1];

    // 1. Check if builtin (not shown here)
    // 2. Check if absolute/relative path (e.g. if cmd_to_find[0] == '/')
    if (cmd_to_find[0] == '/' || cmd_to_find[0] == '.') {
        if (access(cmd_to_find, X_OK) == 0) {
            printf("Command is directly accessible: %s\n", cmd_to_find);
            return 0;
        }
    } else {
    // 3. Search in PATH
        found_path = find_command_in_path(cmd_to_find);
        if (found_path != NULL) {
            printf("Command found in PATH: %s\n", found_path);
            free(found_path);
        } else {
            printf("Command not found: %s\n", cmd_to_find);
        }
    }
    return 0;
}
