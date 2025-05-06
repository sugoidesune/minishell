/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:19:07 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/16 11:06:39 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	init_signals(void);
void	handle_sigquit(int signal);
int		event(void);
void	handle_sigint(int s);
int		signal_heredoc(t_mini *data);
#endif
