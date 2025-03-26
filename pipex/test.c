#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


int main(int argc, char **argv, char **envp)
{
    int fd[2];
    int fd_in;
    int fd_out;
    pid_t pid1;
    pid_t pid2;

    if(argc != 5)
    {
        perror("program requires 4 args!");
        exit(1);
    }
    
    fd_in = open(argv[1], O_RDONLY);
    if(fd_in < 0)
    {
        perror("FD_IN failed!");
        exit(1);
    }
    
    fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_out < 0)
    {
        perror("FD_OUT failed!");
        exit(1);
    }

    if(pipe(fd) < 0)
    {
        perror("PIPE creation failed!");
        exit(1);
    }

    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd[0]);
        if(dup2(fd_in, STDIN_FILENO) < 0)
        {
            perror("PIPE creation failed!");
            exit(1);
        }
        if(dup2(fd[1], STDOUT_FILENO) < 0)
        {
            perror("PIPE creation failed!");
            exit(1);
        }
        execve(argv[2], envp);
        close(fd[1]);
        close(fd[0]);
        
    }



}