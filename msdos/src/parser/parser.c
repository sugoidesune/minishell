/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:22 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 17:40:07 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_lexer	*store_redirection(t_lexer **token, t_parser **pars_node, t_mini *data)
{
	t_lexer	*new_node;
	char	*redirection;
	t_lexer	*new_position;

	redirection = ft_strdup((*token)->next->token);
	if (redirection == NULL)
		free_data_and_exit(data, EXIT_FAILURE);
	new_node = new_node_lexer(redirection, (*token)->type);
	if (new_node == NULL)
		free_data_and_exit(data, EXIT_FAILURE);
	add_node_lexer(new_node, &(*pars_node)->redirections);
	new_position = delete_redirection_lexer(data, token);
	return (new_position);
}

t_lexer	*handle_redirections(t_mini *data, t_lexer *lex_node, t_parser *node)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lex_node;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		if (tmp->type != WORD)
		{
			tmp = store_redirection(&tmp, &node, data);
			if (i == 0)
				lex_node = tmp;
			if (tmp == NULL && i == 0)
				return (NULL);
		}
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	return (lex_node);
}

t_lexer	*store_commands(t_mini *data, t_lexer *tmp, t_parser **parser_node)
{
	int		cmds_num;
	int		i;

	i = 0;
	tmp = handle_redirections(data, tmp, *parser_node);
	cmds_num = count_commands(data, tmp);
	if (cmds_num == 0)
	{
		(*parser_node)->commands = NULL;
		return (tmp);
	}
	(*parser_node)->commands = malloc(sizeof(char *) * (cmds_num + 1));
	if ((*parser_node)->commands == NULL)
		free_data_and_exit(data, EXIT_FAILURE);
	while (tmp && tmp->type != PIPE)
	{
		(*parser_node)->commands[i] = ft_strdup(tmp->token);
		if ((*parser_node)->commands[i] == NULL)
			free_data_and_exit(data, EXIT_FAILURE);
		i++;
		tmp = tmp->next;
	}
	(*parser_node)->commands[i] = NULL;
	return (tmp);
}

t_lexer	*remove_pipe(t_mini *data, t_lexer *tmp)
{
	t_lexer	*new_position;

	new_position = NULL;
	if (tmp == NULL)
		return (NULL);
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
	{
		new_position = tmp->next;
		new_position->prev = tmp->prev;
		if (new_position->prev)
			new_position->prev->next = new_position;
		if (!tmp->prev)
			data->lexer = new_position;
		free(tmp);
	}
	return (new_position);
}

void	parser(t_mini *data)
{
	t_parser	*node;
	t_parser	*parser;
	t_lexer		*tmp;

	tmp = data->lexer;
	node = NULL;
	parser = NULL;
	while (tmp)
	{
		node = new_node_parser(tmp->token);
		if (node == NULL)
			free_data_and_exit(data, EXIT_FAILURE);
		tmp = store_commands(data, tmp, &node);
		add_node_parser(node, &parser);
		tmp = remove_pipe(data, tmp);
	}
	data->parser = parser;
}
