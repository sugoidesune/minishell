/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:35:19 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/18 18:14:10 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	g_status = 0;

void	set_pwd(t_mini *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			data->pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			data->old_pwd = ft_substr(env[i], 7, ft_strlen(env[i]) - 7);
		i++;
	}
}

void	init_data(t_mini *data, char **env)
{
	data->line = NULL;
	data->env = strarr_cpy(env);
	if (data->env == NULL)
		exit(EXIT_FAILURE);
	data->lexer = NULL;
	data->parser = NULL;
	data->pids = NULL;
	data->in_fd = STDIN_FILENO;
	data->exit_code = 0;
	data->env_list = env_list(env);
	set_pwd(data, env);
	init_signals();
}

int	main(int argc, char **argv, char **env)
{
	t_mini		data;

	if (argc > 1 || argv[1])
	{
		printf("No arguments accepted.\n");
		return (EXIT_SUCCESS);
	}
	init_data(&data, env);
	mini_loop(&data);
	return (EXIT_SUCCESS);
}
