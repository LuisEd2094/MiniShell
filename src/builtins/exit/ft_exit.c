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

int	is_only_num(char	*cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (i == 0 && cmd[i] == '-')
			i++;
		else if (!ft_isdigit(cmd[i]))
			return (0);
	}
	return (1);
}

int	print_only_numeric_error(char *cmd)
{
	write(STDERR_FILENO, "minishell: exit: ", ft_strlen("minishell: exit: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": numeric argument required\n", \
			ft_strlen(": numeric argument required\n"));
	exit (255);
}

int	ft_exit(char **cmd, t_minishell *mini)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	if (len > 2)
	{
		if (!is_only_num(cmd[1]))
			return (print_only_numeric_error(cmd[1]));
		else
			return (print_error("minishell: exit: too many arguments\n", 1));
	}
	if (cmd[1] && !is_only_num(cmd[1]))
		print_only_numeric_error(cmd[1]);
	if (cmd[1])
		exit(ft_atoi(cmd[1]));
	return (exit_mini(mini));
}
