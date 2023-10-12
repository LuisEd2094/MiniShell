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

static	void	action(int signal, siginfo_t *info, void *context)
{
	if (info || context)
		info = info;
	if (signal == SIGINT)
	{
		received_signal = SIGINT;
		rl_catch_signals = 1;

		ft_printf("I am sig int \n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		ft_printf(" I am SIGTSTp");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_action(void)
{
	struct sigaction	act;
;
	sigemptyset(&act.sa_mask); 
	act.sa_sigaction = action;
	act.sa_flags = SA_RESTART;
	
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	//sigaction(SIGTSTP, &act, NULL);
}


static	void	child_action(int signal, siginfo_t *info, void *context)
{
	if (info || context)
		info = info;
	if (signal == SIGINT)
	{
		/*rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();*/
		//rl_redisplay();
		rl_catch_signals = 1;

		exit(SIGINT);
	}
	else if (signal == SIGQUIT)
	{
		ft_printf(" I am SIGTSTp");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_action_signal(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask); 
	act.sa_sigaction = child_action;

	act.sa_flags = SA_RESTART;
	received_signal = 0;
	
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}


