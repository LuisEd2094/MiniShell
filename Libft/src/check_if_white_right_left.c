/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_white_right_left.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:10:22 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:10:56 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_if_white_right_left(char	*argv)
{
	if (ft_isspace(argv[0]) || ft_isspace(argv[ft_strlen(argv) - 1]))
		return (1);
	return (0);
}
