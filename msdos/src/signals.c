/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:06:53 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/16 11:41:40 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	signal_heredoc(t_mini *data)
{
	t_parser	*cmd;

	cmd = data->parser;
	while (cmd)
	{
		check_heredoc(data, cmd);
		if (g_status == 130)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	handle_sigint(int s)
{
	if (g_status == 0)
	{
		if (s == SIGINT)
			g_status = 130;
		else if (s == SIGQUIT)
			g_status = 131;
		rl_done = 1;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	sa;

	rl_event_hook = event;
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
