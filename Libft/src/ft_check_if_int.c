/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:11:44 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:12:09 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	check_last_digit(int sign, char *argv, int i)
{
	if (argv[i + 1] != '\0')
		return (0);
	if (sign == -1)
	{
		if ('8' - argv[i] >= 0)
			return (1);
		return (0);
	}
	else
	{
		if ('7' - argv[i] >= 0)
			return (1);
		return (0);
	}
}

static int	get_sign_int(char *argv)
{
	int	sign;
	int	i;

	sign = 0;
	i = 0;
	if ((argv[i] == '-' || argv[i] == '+') && ft_isdigit(argv[i + 1]))
	{
		if (argv[i] == '-' )
			sign = -1;
		else if (argv[i] == '+')
			sign = 1;
		i++;
	}
	else
		sign = 0;
	return (sign);
}

int	check_last_space(char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	check_if_int(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = get_sign_int(str);
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '0')
		i++;
	if (sign)
		i++;
	while (str[i])
	{
		if ((sign && i == 10) || (!sign && i == 9))
			return (check_last_digit(sign, str, i));
		if (ft_isspace(str[i]))
			return (check_last_space(str, i));
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
