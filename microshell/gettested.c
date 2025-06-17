// Function to capture user input

// Assuming you have a libft.h with necessary function declarations
#include "micro.h"


int	(*pipe_store(void))[2]
{
    static int	pipes[10][2];

    return (pipes);
}

void reset_pipes(void)
{
	int (*pipes)[2];
	int i;

	pipes = pipe_store();
	i = 0;
	while (i < 10)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
}

void print_pipe_store_values(void)
{
	int (*pipes)[2];
	int i;

	pipes = pipe_store();
	printf("=== Pipe Store Values ===\n");
	i = 0;
	while (i < 10)
	{
		printf("Pipe[%d]: [%d, %d]\n", i, pipes[i][0], pipes[i][1]);
		i++;
	}
	printf("========================\n");
}

void test_reset_pipes(void)
{
	printf("Before reset:\n");
	print_pipe_store_values();
	
	reset_pipes();
	
	printf("After reset:\n");
	print_pipe_store_values();
}

int	*get_pipe(int index)
{
    int (*pipes)[2];
    
    pipes = pipe_store();
    return (pipes[index]);
}

// ai slop. temporary
char **build_env_arr_temp(void)
{
    char **envp;
    char *path_value;
    char *path_entry;
    int path_len;
    int key_len;
    
    // Allocate array for environment variables (PATH + NULL terminator)
    envp = malloc(sizeof(char *) * 2);
    if (!envp)
        return NULL;
    
    path_value = getenv("PATH");
    if (!path_value)
    {
        envp[0] = ft_strdup("PATH=/bin:/usr/bin");
        envp[1] = NULL;
        return envp;
    }
    
    // Calculate lengths
    key_len = 5; // "PATH="
    path_len = ft_strlen(path_value);
    
    // Allocate memory for "PATH=value"
    path_entry = malloc(key_len + path_len + 1);
    if (!path_entry)
    {
        free(envp);
        return NULL;
    }
    
    // Build the PATH entry
    path_entry[0] = '\0';
    ft_str_append(path_entry, "PATH=");
    ft_str_append(path_entry, path_value);
    
    envp[0] = path_entry;
    envp[1] = NULL;
    
    return envp;
}

void free_strarr(char **envp)
{
    int i;
    
    if (!envp)
        return;
    
    i = 0;
    while (envp[i] != NULL)
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

// WARNING: execvp is not in the allowed functions list. You must use execve.
// This requires implementing PATH searching logic if the command is not a full path.
void	execute_command(char **args)
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

void	print_pipes(int pipes[][2], int command_count)
{
    int	i;

    i = 0;
    while (i < command_count - 1)
    {
        printf("Pipe %d: %d -> %d\n", i, pipes[i][0], pipes[i][1]);
        i++;
    }
}

// we set the last pipe to -1 to indicate no more pipes
bool	create_pipes(int command_count)
{
	int	i;
    int (*pipes)[2];

    pipes = pipe_store();
	// important to intialize the first pipe_store to -1
	reset_pipes();
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
	return (true);
}

// pipe array is terminated with -1
// so as we loop we check if not -1
void	close_all_pipes(int pipes[][2])
{
	int	i;

	i = 0;
	while (pipes[i][0] != -1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}


bool set_input_fd(int fd)
{
	if (dup2(fd, INPUT_FD) == -1)
	{
		// TODO: HANDLE THIS CASE
		perror("microshell");
		exit(EXIT_FAILURE);
	}
	return (true);
}

bool set_output_fd(int fd)
{
	if (dup2(fd, OUTPUT_FD) == -1)
	{
		// TODO: HANDLE THIS CASE
		perror("microshell");
		exit(EXIT_FAILURE);
	}
	return (true);
}
// connect read from previous pipe to input of current process
// connect output of current process to write of current pipe
void	setup_fd_for_fork(int pipes[][2], int command_index, bool to_be_piped, t_command *cmd)
{
	int fd;
	t_list_el *redir_current;
	t_redirection *redir;

	if (command_index > 0)
		set_input_fd(pipes[command_index - 1][0]); // Connect input from previous pipe
	if (to_be_piped)
		set_output_fd(pipes[command_index][1]);

	if (cmd->redirections != NULL)
	{
		redir_current = cmd->redirections->head;
		while (redir_current != NULL)
		{
			redir = (t_redirection *)redir_current->content;
			
			if (redir->type == TOKEN_REDIRECT_OUT)
			{
				fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					perror("microshell");
					exit(1);
				}
				set_output_fd(fd);
				// we can close since it's already duplicated
				// this is tried and tested and works
				close(fd);
			}
			else if (redir->type == TOKEN_APPEND)
			{
				fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					perror("microshell");
					exit(1);
				}
				set_output_fd(fd);
				// we can close since it's already duplicated
				close(fd);
			}
			else if (redir->type == TOKEN_REDIRECT_IN)
			{
				fd = open(redir->filename, O_RDONLY);
				if (fd == -1)
				{
					perror("microshell");
					exit(1);
				}
				set_input_fd(fd);
				// we can close since it's already duplicated
				close(fd);
			}
			
			redir_current = redir_current->next;
		}
	}
}

bool is_builtin(char *cmd_name)
{
    // Check if the command is a built-in command
    return (ft_strcmp(cmd_name, "echo") == 0);
}

bool execute_builtin(t_command *cmd)
{
	// Execute the built-in command
	if (ft_strcmp(cmd->command_name, "echo") == 0)
	{
		bin_echo(cmd->args);
		return true; // Indicate successful execution of built-in command
	}
	return false; // Not a built-in command
}

void	execute_single_command(t_command *cmd)
{
	if (is_builtin(cmd->command_name))
	{
		if (!execute_builtin(cmd))
		{
			perror("microshell");
			exit(EXIT_FAILURE);
		}
		exit(1); // Exit child process after executing builtin
	}
	char *path = path_finder(cmd->command_name);
	if(!path){
		perror("microshell");
		exit(error_code());
	}
	char **envp = build_env_arr_temp();
	if (!envp)
	{
		free(path);
		perror("microshell");
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, envp);
	free_strarr(envp);
	free(path);
	perror("microshell");
	exit(1);
}

pid_t	fork_command(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("microshell");
		return (-1);
	}
	if (pid == IS_CHILD_PROCESS)
	{
		setup_fd_for_fork(pipe_store(), cmd->command_index, cmd->to_be_piped, cmd);
		close_all_pipes(pipe_store());
		execute_single_command(cmd);
	}
	else {
		// Parent process
		cmd->pid = pid;
	}
	return (pid);
}

void	wait_for_all_children(int command_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < command_count)
	{
		wait(&status);
		i++;
	}
}



// void	set_pipe(int index, int read_fd, int write_fd)
// {
//     (*pipe_store())[index][0] = read_fd;
//     (*pipe_store())[index][1] = write_fd;
// }

// int	get_pipe_read(int index)
// {
//     return ((*pipe_store())[index][0]);
// }

// int	get_pipe_write(int index)
// {
//     return ((*pipe_store())[index][1]);
// }

// void	mark_pipe_end(int index)
// {
//     (*pipe_store())[index][0] = -1;
//     (*pipe_store())[index][1] = -1;
// }

// bool	is_pipe_end(int index)
// {
//     return ((*pipe_store())[index][0] == -1);
// }

void for_each_command(t_list *commands, void (*func)(t_command *))
{
    t_list_el	*current;
    t_command	*cmd;

    current = commands->head;
    while (current != NULL)
    {
        cmd = current->content;
        func(cmd);
        current = current->next;
    }
}

void	execute_commands(t_list *commands)
{
	t_list_el	*current_command;
	t_command	*cmd;
	int			command_count;

	current_command = commands->head;
	command_count = count_commands(commands);

	if (!create_pipes(command_count)){
		perror("error creating pipes");
		return ;
	}
	print_pipe_store_values();
    for_each_command(commands, (void (*)(t_command *))fork_command);
	close_all_pipes(pipe_store());
	wait_for_all_children(command_count);
}



int main3(void)
{
    t_list *input_two;
    int command_count;

    printf("=== Testing PATH finder and environment functions ===\n");
    
    input_two = create_input_2();
    command_count = count_commands(input_two);
    printf("Command count: %d\n", command_count);
    
    print_command_list(input_two);
    printf("Executing pipeline: ls -la | grep \\.c | wc -l\n");
    printf("Expected output: Number of .c files in current directory\n");
    printf("vvvvvvvv starting here vvvvvv\n");
    
    execute_commands(input_two);
    
    return (0);
}



int main(void)
{
    char *input;
    t_list *commands;

    while (1)
    {
        input = readline("minishell> ");
        
        if (input == NULL)
        {
            printf("\n");
            break;
        }
        
        if (*input)
        {
            add_history(input);
        }
        
        commands = NULL;
        
        if (ft_strcmp(input, "a") == 0)
        {
            commands = create_input_1();
        }
        else if (ft_strcmp(input, "b") == 0)
        {
            commands = create_input_2();
        }
		else if (ft_strcmp(input, "c") == 0)
        {
            commands = create_input_3();
        }
		else if (ft_strcmp(input, "d") == 0)
        {
            commands = create_input_4();
        }
        else if (ft_strcmp(input, "e") == 0)
        {
            commands = create_input_5();
        }
		else if (ft_strcmp(input, "f") == 0)
        {
            commands = create_input_6();
        }
        else if (ft_strcmp(input, "g") == 0)
        {
            commands = create_input_7();
        }
        else if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        
        if (commands != NULL)
        {
			//printf("Executing commands from input: %s\n", input);
            execute_commands(commands);
        }
        free(input);
    }
    
    rl_clear_history();
    return (0);
}


int	main1(void)
{
	char *input;
	char *args[3];
	// printf("%i\n", ft_atoi("399") + 2); // Print the PID of the shell process
	t_list *input_one = create_input_1();
	t_list_el *current = input_one->head;
	t_command *cmd = current->content;
	// printf("Command: %s\n", cmd->command_name);
	// printf("Args: %s %s\n", cmd->args[0], cmd->args[1]);
	// print_command_list(input_one);
	int command_count = count_commands(input_one);
	printf("Command count: %d\n", command_count);
	execute_commands(input_one);
	return (0); // Return 0 to indicate successful execution
	while (1)
	{
		input = capture_input();
		if (input == NULL)
			// If capture_input returned NULL (EOF in non-TTY mode or ft_strtrim error)
		{
			break ; // Exit the loop and terminate the shell
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
		free(input);



			// free(NULL) is safe if input became NULL (e.g. ft_strtrim error)
	}
	return (0);
}