/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:19:23 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 22:45:06 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	count_words(char **commands)
{
	int		count;
	int		i;
	char	*command;
	int		in_word;
	int		j;

	count = 0;
	i = -1;
	while (commands && commands[++i])
	{
		command = commands[i];
		j = -1;
		in_word = 0;
		while (command[++j])
		{
			if (!isspace(command[j]) && !in_word)
			{
				in_word = 1;
				count++;
			}
			else if (isspace(command[j]))
				in_word = 0;
		}
	}
	return (count);
}

void	replace_marker(char **commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			if (commands[i][j] == '\x03' || commands[i][j] == '\x05')
				commands[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	*copy_word(const char *command, int start, int end)
{
	int		word_length;
	char	*word;

	word_length = end - start;
	word = (char *)malloc((word_length + 1) * sizeof(char));
	if (word == NULL)
		free_data_and_exit((void *)word, 1);
	ft_strncpy(word, ((char *)command + start), word_length);
	word[word_length] = '\0';
	return (word);
}

int	parse_command(char *command, char **result, int index)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (command[start])
	{
		while (command[start] && is_whitespace(command[start]))
			start++;
		end = start;
		while (command[end] && !is_whitespace(command[end]))
			end++;
		if (end > start)
			result[index++] = copy_word(command, start, end);
		start = end;
	}
	return (index);
}

char	**make_commands_cpy(char **commands)
{
	int		total_words;
	char	**result;
	int		index;
	int		i;

	total_words = count_words(commands);
	result = (char **)malloc((total_words + 1) * sizeof(char *));
	if (result == NULL)
		free_data_and_exit((void *)result, 1);
	index = 0;
	i = 0;
	while (commands && commands[i])
	{
		index = parse_command(commands[i], result, index);
		i++;
	}
	result[index] = NULL;
	replace_marker(result);
	return (result);
}
