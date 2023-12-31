/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:00:49 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 13:06:07 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "../../readline/readline.h"

static	void	action(int signal)
{
	if (signal == SIGINT)
	{
		g_received_signal = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signal_action(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = action;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static	void	pipe_action(int signal)
{
	if (signal == SIGINT)
	{
		g_received_signal = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	pipe_signal_action(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = pipe_action;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}
