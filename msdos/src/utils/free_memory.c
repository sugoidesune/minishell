/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:11:02 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/19 22:45:49 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	free_strarr(char **strarr)
{
	int	i;

	i = 0;
	while (strarr && strarr[i])
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
	strarr = NULL;
}

void	free_parser_list(t_parser **parser_list)
{
	t_parser	*tmp;
	t_parser	*next;

	tmp = *parser_list;
	while (tmp)
	{
		next = tmp->next;
		free_node_parser(&tmp);
		tmp = next;
	}
	*parser_list = NULL;
}

void	free_lexer_list(t_lexer **lexer_list)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = *lexer_list;
	while (tmp)
	{
		next = tmp->next;
		free_node_lexer(&tmp);
		tmp = next;
	}
	*lexer_list = NULL;
}

void	free_data_and_exit(t_mini *data, int exit_code)
{
	if (data->line != NULL)
		free(data->line);
	if (data->env != NULL)
		free_strarr(data->env);
	if (data->lexer != NULL)
		free_lexer_list(&data->lexer);
	if (data->parser != NULL)
		free_parser_list(&data->parser);
	if (data->env_list != NULL)
		free_env_list(data->env_list);
	exit (exit_code);
}
