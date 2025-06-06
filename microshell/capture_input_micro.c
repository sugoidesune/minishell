/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture_input_micro.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:52:46 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/05 16:52:51 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro.h"

char	*capture_input(void)
{
	char *input;
	char *line;

	input = NULL;
	// line will be initialized if the else branch is taken

	if (isatty(fileno(stdin))) // Check if input is from a terminal
	{
		input = readline("microshell> "); // Get input with a prompt
		if (input == NULL)                // Ctrl+D returns NULL
		{
			write(1, "\n", 1);       // Newline for clean exit
			exit(0);                   // Exit the shell
		}
	}
	else // Input is not from a terminal (e.g., piped from tester)
	{
		// You must have a working get_next_line function available.
		line = get_next_line(fileno(stdin)); 
		if (line == NULL) // EOF or error from get_next_line
		{
			return (NULL); // Signal to main loop to terminate
		}
		// You must have a working ft_strtrim function (or equivalent) available.
		input = ft_strtrim(line, "\n"); 
		free(line);                     // Free the line read by get_next_line
		// If ft_strtrim fails (e.g. malloc error), input might be NULL.
		// This will be handled by the main loop.
	}
	return (input);
}

// Function to parse input into commands and arguments
// WARNING: strtok is not in the allowed functions list. This function needs to be rewritten
// using functions from your libft or implemented from scratch.
void	parse_input(char *input, char **args)
{
	int		i;
	char	*token;

	i = 0;
	token = strtok(input, " ");
	while (token != NULL && i < 3 - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL; // Null-terminate the array
}