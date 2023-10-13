/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:15:12 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 13:15:58 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "../readline/readline.h"

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
;
	sigemptyset(&act.sa_mask); 
	act.sa_handler  = action;
	act.sa_flags = SA_RESTART;
	
	sigaction(SIGINT, &act, NULL);
    signal(SIGQUIT, SIG_IGN);
}

void	child_action(int signal)
{
	if (signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		g_received_signal = SIGINT;
	}
}

void	child_action_signal(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask); 
	act.sa_handler  = child_action;
	act.sa_flags = SA_RESTART;
	g_received_signal = 0;
	
	sigaction(SIGINT, &act, NULL);
    signal(SIGQUIT, SIG_IGN);
}


