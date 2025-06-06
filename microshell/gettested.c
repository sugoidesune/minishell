// Function to capture user input


// Assuming you have a libft.h with necessary function declarations
#include "micro.h"

int IS_CHILD_PROCESS = 0;

// WARNING: execvp is not in the allowed functions list. You must use execve.
// This requires implementing PATH searching logic if the command is not a full path.
void execute_command(char **args)
{
    pid_t	pid;
    int		status;

    pid = fork();
    if (pid < 0)
        perror("microshell");
        
    if (pid == IS_CHILD_PROCESS)
    {
        execvp(args[0], args);
        perror("microshell");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        waitpid(pid, &status, 0);
    }
}

void print_pipes(int pipes[][2], int command_count)
{
	int i;

	for (i = 0; i < command_count - 1; i++)
	{
		printf("Pipe %d: %d -> %d\n", i, pipes[i][0], pipes[i][1]);
	}
}

// we set the last pipe to -1 to indicate no more pipes
bool create_pipes(int pipes[][2], int command_count)
{
        int i;

        i = 0;
        while (i < command_count - 1)
        {
            if (pipe(pipes[i]) == -1)
            {
                perror("pipe");
                return (false);
            }
            i++;
        }
        pipes[i][0] = -1;
        pipes[i][1] = -1;
        return (true);
}

// pipe array is terminated with -1
// so as we loop we check if not smaller than 0
void close_all_pipes(int pipes[][2])
{
    int i;

    i = 0;
    while (pipes[i][0] != -1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void setup_input_pipe(int pipes[][2], int command_index)
{
    if (command_index > 0)
        dup2(pipes[command_index - 1][0], 0);
}

void setup_output_pipe(int pipes[][2], int command_index, bool to_be_piped)
{
    if (to_be_piped)
        dup2(pipes[command_index][1], 1);
}

void execute_single_command(t_command *cmd, int pipes[][2], int command_index, int pipe_count)
{
    setup_input_pipe(pipes, command_index);
    setup_output_pipe(pipes, command_index, cmd->to_be_piped);
    close_all_pipes(pipes);
    execvp(cmd->args[0], cmd->args);
    perror("microshell");
    exit(1);
}

pid_t fork_command(t_command *cmd, int pipes[][2], int command_index, int pipe_count)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("microshell");
        return (-1);
    }
    if (pid == IS_CHILD_PROCESS)
        execute_single_command(cmd, pipes, command_index, pipe_count);
    return (pid);
}

void wait_for_all_children(int command_count)
{
    int status;
    int i;

    i = 0;
    while (i < command_count)
    {
        wait(&status);
        i++;
    }
}

void execute_commands(t_list *commands)
{
    t_list_el *current_command;
    t_command *cmd;
    int pipes[10][2]; // SET MAX COMMAND COUNT HERE
    int command_count;
    int command_index;
    int pipe_count;

    current_command = commands->head;
    command_count = count_commands(commands);
    command_index = 0;
    pipe_count = command_count - 1;


    if (command_count > 1)
        if (!create_pipes(pipes, command_count))
            return;

    while (current_command != NULL)
    {
        cmd = current_command->content;
        fork_command(cmd, pipes, command_index, pipe_count);
        current_command = current_command->next;
        command_index++;
    }

    if (command_count > 1)
        close_all_pipes(pipes, pipe_count);
    wait_for_all_children(command_count);
}

int	main(void)
{
	char *input;
	char *args[3];
	//printf("%i\n", ft_atoi("399") + 2); // Print the PID of the shell process
	t_list *input_one = create_input_1();
	t_list_el *current = input_one->head;
	t_command *cmd = current->content;
	//printf("Command: %s\n", cmd->command_name);
	//printf("Args: %s %s\n", cmd->args[0], cmd->args[1]);
	//print_command_list(input_one);
	int command_count = count_commands(input_one);
	printf("Command count: %d\n", command_count);
	execute_commands(input_one);
	return (0); // Return 0 to indicate successful execution
	while (1)
	{
		input = capture_input();
		if (input == NULL) // If capture_input returned NULL (EOF in non-TTY mode or ft_strtrim error)
		{
			break; // Exit the loop and terminate the shell
		}
		// The tester instructions mention commenting out prints like "exit".
		// The current Ctrl+D handling in interactive mode prints a newline and exits.
		// This should be fine, but be mindful of any unexpected output.

		// If using readline, you might want to add non-empty inputs to history:
		// if (isatty(fileno(stdin)) && input && *input)
		// {
		//     add_history(input); // add_history is an allowed function
		// }

		parse_input(input, args);
		if (args[0] != NULL)
		{
			execute_command(args);
		}
		free(input); // free(NULL) is safe if input became NULL (e.g. ft_strtrim error)
	}
	return (0);
}