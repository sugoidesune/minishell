/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:07:54 by codespace         #+#    #+#             */
/*   Updated: 2024/12/19 21:10:35 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->variable);
		free(tmp->content);
		free(tmp);
		tmp = next;
	}
}

void	free_t_content(t_content *content)
{
	if (content)
	{
		if (content->variable)
			free(content->variable);
		if (content->content)
			free(content->content);
	}
}

long long	length_2(long long exit_code, t_mini *data)
{
	if (exit_code == LLONG_MAX)
	{
		printf("exit: %s: value too large\n", data->parser->commands[1]);
		free_data_and_exit(data, 2);
	}
	if (exit_code < 0 || exit_code > 255)
		exit_code = exit_code % 256;
	printf("exit\n");
	return (exit_code);
}
