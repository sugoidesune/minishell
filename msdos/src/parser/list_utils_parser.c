/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:18:39 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/10 13:31:13 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	count_nodes(t_parser *parser_list)
{
	int			nodes;
	t_parser	*tmp;

	nodes = 0;
	tmp = parser_list;
	while (tmp)
	{
		nodes++;
		tmp = tmp->next;
	}
	return (nodes);
}

void	free_node_parser(t_parser **node)
{
	t_lexer	*tmp;
	t_lexer	*next;

	if (*node)
	{
		if ((*node)->commands != NULL)
			free_strarr((*node)->commands);
		if ((*node)->heredoc_delim != NULL)
			free((*node)->heredoc_delim);
		if ((*node)->heredoc_name != NULL)
			free((*node)->heredoc_name);
		if ((*node)->redirections != NULL)
		{
			tmp = (*node)->redirections;
			while (tmp)
			{
				next = tmp->next;
				free(tmp->token);
				free(tmp);
				tmp = next;
			}
		}
		free(*node);
		*node = NULL;
	}
}

t_parser	*new_node_parser(char *cmd)
{
	t_parser	*new_node;

	new_node = malloc(sizeof(t_parser));
	if (new_node == NULL)
		return (NULL);
	new_node->commands = NULL;
	new_node->redirections = NULL;
	new_node->builtin = check_builtin(cmd);
	new_node->heredoc_name = NULL;
	new_node->heredoc_delim = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_node_parser(t_parser *new_node, t_parser **parser_list)
{
	t_parser	*temp_node;

	temp_node = *parser_list;
	if (*parser_list == NULL)
	{
		*parser_list = new_node;
		return ;
	}
	while (temp_node->next != NULL)
		temp_node = temp_node->next;
	temp_node->next = new_node;
	new_node->prev = temp_node;
}
