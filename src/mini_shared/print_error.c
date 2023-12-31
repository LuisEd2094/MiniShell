/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:35:08 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:35:23 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>

int	print_error(char *err_description, int err_value)
{
	write(STDERR_FILENO, err_description, ft_strlen(err_description));
	return (err_value);
}

void	*print_perror(void)
{
	perror("minishell ");
	return (NULL);
}
