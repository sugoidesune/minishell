#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "micro.h"


char *path_concat(char *path, char *filename)
{
    char *full_path;
    size_t path_len;
    size_t filename_len;
    
    path_len = ft_strlen(path);
    filename_len = ft_strlen(filename);
    
    full_path = malloc(path_len + filename_len + 2);
    if (!full_path)
        return NULL;
    full_path[0] = '\0';

    ft_str_append(full_path, path);
    if (path[path_len - 1] != '/')
        ft_str_append(full_path, "/");
    ft_str_append(full_path, filename);
    
    return full_path;
}

int ft_str_contains(char *str, char c)
{
    int i;

    if (!str)
        return 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

bool is_executable(char *path)
{
    return (access(path, X_OK) == 0);
}

bool is_exists(char *path)
{
    return (access(path, F_OK) == 0);
}

bool is_path(char *path){
    return ft_str_contains(path, '/');
}

char *get_validated_path(char *path)
{
    if(!is_exists(path))
        return set_error(ERR_NOT_FOUND);
    if(!is_executable(path))
        return set_error(ERR_NOT_EXECUTABLE);
    return ft_strdup(path);
}

// a function that takes a ft_split array of paths, which is bull terminated
// and a filename, and returns the first path that contains the file.
char *search_paths(char **paths, char *filename)
{
    int i;
    char *full_path;

    if (!paths || !filename)
        return NULL;

    i = 0;
    while (paths[i] != NULL)
    {
        full_path = path_concat(paths[i], filename);
        if (!full_path)
            return NULL;
        if (is_executable(full_path))
            return full_path;
        free(full_path);
        i++;
    }
    return NULL;
}


bool is_valid_path_env(char *path_env)
{
    if (!path_env || ft_strlen(path_env) == 0)
        return false;
    return true;
}

char *path_finder(char *command){
    char *path_env;
    char **path_dirs;
    char *result;

    if (!command)
        return NULL;

    // Check if the command is an absolute or relative path
    if(is_path(command))
        return get_validated_path(command);
    path_env = getenv("PATH");
    // If PATH is not set, return an error
    if (!is_valid_path_env(path_env))
        return set_error(ERR_NOT_FOUND);
    // Split the PATH environment variable into directories
    path_dirs = ft_split(path_env, ':');
    if (!path_dirs)
        return set_error(ERR_MALLOC);
    // Search for the command in the directories
    result = search_paths(path_dirs, command);
    free_ft_split_array(path_dirs);
    
    return result;
}


// int main(void)
// {
//     char *test_commands[4];
//     char *test_descriptions[4];
//     char *found_path;
//     int i;

//     test_commands[0] = "/bin/ls";
//     test_commands[1] = "./test_executable";
//     test_commands[2] = "ls";
//     test_commands[3] = NULL;

//     test_descriptions[0] = "=== Testing absolute path ===";
//     test_descriptions[1] = "=== Testing relative path ===";
//     test_descriptions[2] = "=== Testing simple command 'ls' ===";
//     test_descriptions[3] = NULL;

//     i = 0;
//     while (test_commands[i] != NULL)
//     {
//         printf("%s\n", test_descriptions[i]);
//         found_path = path_finder(test_commands[i]);
//         if (found_path)
//         {
//             printf("Found: %s\n", found_path);
//             free(found_path);
//         }
//         else
//         {
//                 printf("Not found or not executable.\n");
//         }
//         i++;
//     }

//     return 0;
// }

// int main(void)
// {
//     char *path_env;
//     char *test_file;
//     struct stat file_stat;
//     int access_result;
//     int stat_result;
//     char **path_dirs;
//     char *found_path;

//     path_env = getenv("PATH");
//     test_file = "/bin/ls";

//     if (path_env)
//         printf("PATH: %s\n", path_env);
//     else
//         printf("PATH not found\n");
    
//     path_dirs = ft_split(path_env, ':');

//     if (!path_dirs)
//         return (0); // Handle malloc failur
//     found_path = search_paths(path_dirs, "ran123");
//     free_ft_split_array(path_dirs); // Free the split array
//     if (found_path)
//     {
//         printf("Found file at: %s\n", found_path);
//         free(found_path); // Free the found path
//     }
//     else
//     {
//         printf("File not found in any PATH directories\n");
//     }
// }

// int mains(void)
// {
//     char *path_env;
//     char *test_file;
//     struct stat file_stat;
//     int access_result;
//     int stat_result;
//     char **path_dirs;
//     char *found_path;

//     path_env = getenv("PATH");
//     test_file = "/bin/ls";

//     if (path_env)
//         printf("PATH: %s\n", path_env);
//     else
//         printf("PATH not found\n");
    
//     path_dirs = ft_split(path_env, ':');

//     if (!path_dirs)
//         return (0); // Handle malloc failur
//     found_path = find_file_in_paths(path_dirs, "ls");
//     if (found_path)
//     {
//         printf("Found file at: %s\n", found_path);
//         free(found_path); // Free the found path
//     }
//     else
//     {
//         printf("File not found in any PATH directories\n");
//     }
//     return (0);

//     access_result = access(test_file, F_OK);
//     if (access_result == 0)
//         printf("File %s exists\n", test_file);
//     else
//         printf("File %s does not exist\n", test_file);

//     stat_result = stat(test_file, &file_stat);
//     if (stat_result == 0)
//         printf("File size: %ld bytes\n", file_stat.st_size);
//     else
//         printf("Could not get file stats\n");

//     return (0);
// }