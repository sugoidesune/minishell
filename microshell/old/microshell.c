#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 10
#define MAX_CMDS 3

// Function to capture user input
char	*capture_input(void)
{
	char *input = readline("microshell> "); // Get input with a prompt
	if (input == NULL)
	{                      // Ctrl+D returns NULL
		write(1, "\n", 1); // Newline for clean exit
		exit(0);           // Exit the shell
	}
	return (input);
}

// Function to parse input into commands and arguments
void	parse_input(char *input, char **args)
{
	int		i;
	char	*token;

	i = 0;
	token = strtok(input, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL; // Null-terminate the array
}

// Function to split commands by pipes
int	split_by_pipes(char **args, char ***cmds)
{
	int	i;
	int	cmd_idx;
	int	arg_idx;
	int	start;

	i = 0;
	cmd_idx = 0;
	start = 0;
	while (args[i] != NULL && cmd_idx < MAX_CMDS)
	{
		if (strcmp(args[i], "|") == 0)
		{
			args[i] = NULL; // Terminate the previous command
			cmds[cmd_idx] = &args[start];
			cmd_idx++;
			start = i + 1;
		}
		i++;
	}
	// Add the last command
	if (start < i && cmd_idx < MAX_CMDS)
	{
		cmds[cmd_idx] = &args[start];
		cmd_idx++;
	}
	return (cmd_idx);
}

// Function to execute commands with pipes
void	execute_piped_commands(char **args)
{
	char	**cmds[MAX_CMDS];
	int		pipes[MAX_CMDS - 1][2];
	int		cmd_count;
	pid_t	pids[MAX_CMDS];
	int		i;
	int		j;

	cmd_count = split_by_pipes(args, cmds);
	// Create necessary pipes
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return ;
		}
		i++;
	}
	// Create processes for each command
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// Child process
			// Set up input from previous pipe (if not first command)
			if (i > 0)
			{
				dup2(pipes[i - 1][0], STDIN_FILENO);
			}
			// Set up output to next pipe (if not last command)
			if (i < cmd_count - 1)
			{
				dup2(pipes[i][1], STDOUT_FILENO);
			}
			// Close all pipes in child
			j = 0;
			while (j < cmd_count - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			// Execute command
			if (strcmp(cmds[i][0], "cat") == 0)
			{
				execl("/bin/cat", "cat", cmds[i][1], NULL);
			}
			else if (strcmp(cmds[i][0], "rev") == 0)
			{
				execl("/usr/bin/rev", "rev", NULL);
			}
			else if (strcmp(cmds[i][0], "wc") == 0 && cmds[i][1] != NULL
				&& strcmp(cmds[i][1], "-l") == 0)
			{
				execl("/usr/bin/wc", "wc", "-l", NULL);
			}
			perror("execl");
			exit(1);
		}
		i++;
	}
	// Close all pipe ends in parent
	// especially the write end pipes[i][1]
	// since the child process will never reach EOF if we don't close it
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	// Wait for all child processes
	i = 0;
	while (i < cmd_count)
	{
		
		//General: Waits specifically for the child process whose PID is pids[i] to terminate or change state. NULL means we don't care about the detailed exit status. 0 means wait for the child to terminate. It ensures the parent waits for this specific child.
		
		//Example: The parent loops through the pids array and waits for each child process (each command in the pipeline) to complete, ensuring the entire pipeline is finished.
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

// Function to check if command contains a pipe
bool	has_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "|") == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

// Function to execute the command
void	execute_command(char **args)
{
	pid_t	pid;

	if (has_pipe(args))
	{
		execute_piped_commands(args);
		return ;
	}
	if (strcmp(args[0], "echo") == 0)
	{
		if (args[1] != NULL)
		{
			write(1, args[1], strlen(args[1]));
			write(1, "\n", 1);
		}
	}
	else if (strcmp(args[0], "mkdir") == 0)
	{
		if (args[1] != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execl("/bin/mkdir", "mkdir", args[1], NULL);
				exit(1);
			}
			else
			{
				wait(NULL);
			}
		}
	}
	else if (strcmp(args[0], "cat") == 0)
	{
		if (args[1] != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execl("/bin/cat", "cat", args[1], NULL);
				exit(1);
			}
			else
			{
				//( non-piped commands):
				//General: Waits for any child process of the calling process to terminate. If there are multiple children, wait returns when the first one finishes. NULL again ignores the exit status.
				//Example: In the simpler execute_command function, when only one command is run (no pipes), the parent forks just one child and uses wait(NULL) to wait for that single child to finish. It's simpler than waitpid when you only have one child you're immediately waiting for.
				wait(NULL);
			}
		}
	}
	else if (strcmp(args[0], "rev") == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execl("/usr/bin/rev", "rev", NULL);
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
}

// Main loop
int	main(void)
{
	char *input;
	char *args[MAX_ARGS];

	while (1)
	{
		input = capture_input();
		parse_input(input, args);
		if (args[0] != NULL)
		{
			execute_command(args);
		}
		free(input);
	}
	return (0);
}