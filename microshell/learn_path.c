#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "micro.h"

int main(void)
{
    char *path_env;
    char *test_file;
    struct stat file_stat;
    int access_result;
    int stat_result;
    char **path_dirs;
    char *found_path;

    path_env = getenv("PATH");
    test_file = "/bin/ls";

    if (path_env)
        printf("PATH: \n%s\n", path_env);
    else
        printf("PATH not found\n");
    
    if (found_path)
    {
        printf("Found file at: %s\n", found_path);
        free(found_path); // Free the found path
    }
    else
    {
        printf("File not found in any PATH directories\n");
    }
    return (0);

    access_result = access(test_file, F_OK);
    if (access_result == 0)
        printf("File %s exists\n", test_file);
    else
        printf("File %s does not exist\n", test_file);

    stat_result = stat(test_file, &file_stat);
    if (stat_result == 0)
        printf("File size: %ld bytes\n", file_stat.st_size);
    else
        printf("Could not get file stats\n");

    return (0);
}