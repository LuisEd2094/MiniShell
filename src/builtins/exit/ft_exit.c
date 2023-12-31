/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:41 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:00:01 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

static int	get_pos(char *cmd, int move, int pos)
{
	if (pos < 0)
		return (0);
	while (pos >= 0 && cmd[pos] && ft_isspace(cmd[pos]))
		pos += move;
	return (pos);
}

int	is_only_num(char *cmd)
{
	int	i;
	int	j;

	i = get_pos(cmd, 1, 0);
	j = get_pos(cmd, -1, ft_strlen(cmd) - 1);
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	if (i > j && !ft_isdigit(cmd[i]))
		return (0);
	if (j < 0)
		return (0);
	while (i <= j)
	{
		if (!ft_isdigit(cmd[j--]) || !ft_isdigit(cmd[i++]))
			return (0);
	}
	return (1);
}

void	print_only_numeric_error(char *cmd, t_minishell *mini)
{
	write(STDERR_FILENO, "minishell: exit: ", ft_strlen("minishell: exit: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": numeric argument required\n", \
			ft_strlen(": numeric argument required\n"));
	mini->exit_code = 255;
	exit_mini(mini);
}

int	ft_exit(char **cmd, t_minishell *mini)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	if (len > 2)
	{
		if (!is_only_num(cmd[1]) || !cmd[1][0])
			print_only_numeric_error(cmd[1], mini);
		else
			return (print_error("minishell: exit: too many arguments\n", 1));
	}
	if ((cmd[1] && !is_only_num(cmd[1])) || (cmd[1] && !cmd[1][0]))
		print_only_numeric_error(cmd[1], mini);
	if (cmd[1])
	{
		if (!check_if_int(cmd[1]))
			print_only_numeric_error(cmd[1], mini);
		mini->exit_code = ft_atoi(cmd[1]);
	}
	return (exit_mini(mini));
}
