/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_identifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:27:59 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:28:48 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdbool.h>
#include <shared.h>

static bool	check_unset(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (1);
	i = -1;
	while (arg[++i])
	{
		if (ft_isdigit(arg[i]) && i == 0)
			return (1);
		else if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
	}
	return (0);
}

static bool	check_export(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (1);
	i = -1;
	while (arg[++i])
	{
		if (ft_isdigit(arg[i]) && i == 0)
			return (1);
		else if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
			return (1);
		else if (arg[i] == '+' && arg[i + 1])
			return (1);
	}
	return (0);
}

int	print_invalid_identifier(char *cmd, char *arg)
{
	print_error("minishell: ", 1);
	print_error(cmd, 1);
	print_error(arg, 1);
	return (print_error("': not a valid identifier\n", 1));
}

int	check_valid_identifier(char *arg, int order)
{
	if (order == EXPORT)
		return (check_export(arg));
	else
		return (check_unset(arg));
}
