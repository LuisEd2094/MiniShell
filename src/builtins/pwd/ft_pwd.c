/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:54:40 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/02 08:55:27 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	ft_pwd(char **arguments)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (arguments == NULL)
		return (-1);
	if (current_directory == NULL)
	{
		perror("Error al obtener el directorio actual");
		return (-1);
	}
	ft_printf("%s\n", current_directory);
	free(current_directory);
	return (0);
}
