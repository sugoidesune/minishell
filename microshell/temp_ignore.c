void execute_commands(t_list *commands)
{
    t_list_el *current_command;
    t_command *cmd;
    int pipes[10][2];
    int command_count;
    int command_index;
    pid_t pid;
    int status;
    int i;

    current_command = commands->head;
    command_count = count_commands(commands);
    command_index = 0;

    if (command_count > 1)
    {
        if (!create_pipes(pipes, command_count))
            return;
    }

    while (current_command != NULL)
    {
        cmd = current_command->content;
        pid = fork();
        
        if (pid < 0)
        {
            perror("microshell");
            return;
        }
        
        if (pid == IS_CHILD_PROCESS)
        {
            // Handle input redirection for piped commands
            if (command_index > 0)
            {
                dup2(pipes[command_index - 1][0], 0);
            }
            
            // Handle output redirection for piped commands
            if (command_index < command_count - 1 && cmd->to_be_piped)
            {
                dup2(pipes[command_index][1], 1);
            }
            
            // Close all pipe file descriptors in child
            i = 0;
            while (i < command_count - 1)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
                i++;
            }
            
            execve(cmd->args[0], cmd->args, NULL);
            perror("microshell");
            exit(1);
        }
        
        current_command = current_command->next;
        command_index++;
    }
    
    // Close all pipe file descriptors in parent
    i = 0;
    while (i < command_count - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
    
    // Wait for all children
    i = 0;
    while (i < command_count)
    {
        wait(&status);
        i++;
    }
}