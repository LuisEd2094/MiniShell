/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_words_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:17:04 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/05/10 16:53:05 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	put_char(int c)
{
	if (write (STDOUT_FILENO, &c, 1) != 1)
		return (-1);
	return (1);
}

int	put_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (put_char(s[i]) == -1)
			return (ft_free_strs(&s, 0, 0));
		i++;
	}
	ft_free_strs(&s, 0, 0);
	return (i);
}
