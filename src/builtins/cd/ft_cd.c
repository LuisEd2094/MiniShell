/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:50:32 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/02 08:52:29 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	check_home(char *home_directory)
{
	if (home_directory == NULL)
	{
		perror("No se pudo obtener el directorio de inicio");
		return (-1);
	}
	if (chdir(home_directory) == -1)
	{
		perror("Error al cambiar al directorio de inicio");
		return (-1);
	}
	return (0);
}

int	ft_cd(char **arguments)
{
	char	*home_directory;

	home_directory = getenv("HOME");
	if (arguments == NULL)
		return (-1);
	if (arguments[1] == NULL)
	{
		if (check_home(home_directory) == -1)
			return (-1);
	}
	else
	{
		if (chdir(arguments[1]) == -1)
		{
			perror("Error al cambiar de directorio");
			return (-1);
		}
	}
	return (0);
}
