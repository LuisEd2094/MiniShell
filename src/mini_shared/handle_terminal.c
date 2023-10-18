/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:28:50 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:28:56 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reset_terminal(t_minishell *mini)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(mini->old));
}

void	prep_terminal(t_minishell *mini)
{
	tcgetattr(STDIN_FILENO, &(mini->old));
	mini->new = mini->old;
	mini->new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(mini->new));
}
