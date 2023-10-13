/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_white_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:13:11 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:13:32 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	remove_white_space(char *argv)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	if (ft_isspace(argv[i]))
	{
		while (ft_isspace(argv[i]))
			i++;
		k = 0;
		while (argv[i])
			argv[k++] = argv[i++];
		while (argv[k])
			argv[k++] = '\0';
	}
	len = ft_strlen(argv) - 1;
	if (ft_isspace(argv[len]))
	{
		while (ft_isspace(argv[len]))
			argv[len--] = '\0';
	}
}
