/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:35:34 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 19:03:43 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	clear_data(t_mini *data)
{
	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->lexer)
	{
		free_lexer_list(&data->lexer);
		data->lexer = NULL;
	}
	if (data->parser)
	{
		free_parser_list(&data->parser);
		data->parser = NULL;
	}
	if (data->pids != NULL)
	{
		free(data->pids);
		data->pids = NULL;
	}
	data->in_fd = STDIN_FILENO;
	g_status = 0;
}

int	continue_case(t_mini *data, char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		return (1);
	if (line[0] == '\t')
		return (1);
	if (count_quotes(data, line))
		return (1);
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (0);
		i++;
		if (line[i] == '\0')
			return (1);
	}
	return (0);
}

void	mini_loop(t_mini *data)
{
	while (1)
	{
		clear_data(data);
		data->line = readline("minishell$ " );
		if (g_status != 0)
		{
			data->exit_code = g_status;
			continue ;
		}
		if (!data->line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit (EXIT_SUCCESS);
		}
		if (continue_case(data, data->line))
			continue ;
		add_history(data->line);
		read_token(data);
		if (unexpected_token_error(data, error_check(data)))
			continue ;
		parser(data);
		if (expander(data))
			continue ;
		executor(data);
	}
}
