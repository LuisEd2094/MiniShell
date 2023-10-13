/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:52:45 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/02 08:54:04 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	ft_flag_n(char *arguments)
{
	int	i;

	i = 0;
	if (arguments[0] == '-' && arguments[1] == 'n')
	{
		while (arguments[++i])
		{
			if (arguments[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **arguments)
{
	int	i;
	int	flag_n;

	i = 0;
	flag_n = 0;
	if (arguments == NULL)
		return (-1);
	if (arguments[1] != NULL && ft_flag_n(arguments[1]))
	{
		flag_n = 1;
		i++;
	}
	while (arguments[++i] != NULL)
	{
		ft_printf("%s", arguments[i]);
		if (arguments[i + 1] != NULL)
			ft_printf(" ");
	}
	if (!flag_n)
		ft_printf("\n");
	return (0);
}
