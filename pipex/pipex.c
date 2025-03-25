#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
/*
Your program should be executed as follows:
./pipex file1 cmd1 cmd2 file2
It must take 4 arguments:
• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly like the following shell command:
$> < file1 cmd1 | cmd2 > file2

III.1 Examples
$> ./pipex infile "ls -l" "wc -l" outfile
Its behavior should be equivalent to: < infile ls -l | wc -l > outfile
$> ./pipex infile "grep a1" "wc -w" outfile
Its behavior should be equivalent to: < infile grep a1 | wc -w > outfile
III.2 Requirements
Your project must comply with the following rules:
• You must submit a Makefile that compiles your source files. It must not perform
unnecessary relinking.
• Your program must never terminate unexpectedly (e.g., segmentation fault, bus
error, double free, etc.).
• Your program must not have memory leaks.
• If you are unsure, handle errors the same way as the shell command:
< file1 cmd1 | cmd2 > file2
*/

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

char **parse_cmd(char *cmd)
{
    char **args = NULL;
    int i = 0;
    int count = 1;
    
    // Count number of spaces to determine number of arguments
    for (int j = 0; cmd[j]; j++)
        if (cmd[j] == ' ')
            count++;
    
    args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        error_exit("malloc failed");
    
    // Split command by spaces
    char *token = strtok(cmd, " ");
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    
    return args;
}

void execute_cmd(char *cmd, char **envp)
{
    char **args = parse_cmd(cmd);
    char *paths = NULL;
    char *path = NULL;
    char full_path[1024];
    
    // Find PATH environment variable
    for (int i = 0; envp[i]; i++)
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            paths = strdup(envp[i] + 5);
            break;
        }
    }
    
    if (!paths)
        error_exit("PATH environment variable not found");
    
    // Try each path in PATH
    path = strtok(paths, ":");
    while (path != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, args[0]);
        execve(full_path, args, envp);
        path = strtok(NULL, ":");
    }
    
    // If we get here, command was not found
    fprintf(stderr, "Command not found: %s\n", args[0]);
    free(args);
    free(paths);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
    int fd[2];
    int fd_in;
    int fd_out;
    pid_t pid1, pid2;

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open input file
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0)
        error_exit("Error opening input file");
    
    // Open output file
    fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0)
        error_exit("Error opening output file");
    
    // Create pipe
    if (pipe(fd) < 0)
        error_exit("Error creating pipe");
    
    // Fork for the first command
    pid1 = fork();
    
    if (pid1 < 0)
        error_exit("Fork failed");
    
    if (pid1 == 0)
    {
        // Child process for cmd1
        close(fd[0]); // Close read end of pipe
        
        // Redirect stdin to input file
        if (dup2(fd_in, STDIN_FILENO) < 0)
            error_exit("dup2 failed");
        
        // Redirect stdout to pipe
        if (dup2(fd[1], STDOUT_FILENO) < 0)
            error_exit("dup2 failed");
        
        // Close unnecessary file descriptors
        close(fd_in);
        close(fd[1]);
        close(fd_out);
        
        execute_cmd(argv[2], envp);
        exit(EXIT_FAILURE); // Should not reach here
    }
    
    // Fork for the second command
    pid2 = fork();
    
    if (pid2 < 0)
        error_exit("Fork failed");
    
    if (pid2 == 0)
    {
        // Child process for cmd2
        close(fd[1]); // Close write end of pipe
        
        // Redirect stdin from pipe
        if (dup2(fd[0], STDIN_FILENO) < 0)
            error_exit("dup2 failed");
        
        // Redirect stdout to output file
        if (dup2(fd_out, STDOUT_FILENO) < 0)
            error_exit("dup2 failed");
        
        // Close unnecessary file descriptors
        close(fd_in);
        close(fd[0]);
        close(fd_out);
        
        execute_cmd(argv[3], envp);
        exit(EXIT_FAILURE); // Should not reach here
    }
    
    // Parent process
    close(fd[0]);
    close(fd[1]);
    close(fd_in);
    close(fd_out);
    
    // Wait for both child processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}