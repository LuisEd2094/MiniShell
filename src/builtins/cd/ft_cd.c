 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:50:32 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/05 14:51:47 by galo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	send_old_directory(t_list *env_list, char *sol)
{
	char	*old_directory;
	
	old_directory = malloc((ft_strlen("OLDPWD") + 1) * sizeof(char));
	if (old_directory == NULL)
	{
		perror("Error OLDPWD: Fallo en malloc");
		return (3);
	}
	if (sol == NULL)
	{
		free(old_directory);
		perror("Error OLDPWD: Fallo en malloc");
		return (3);
	}
	ft_strlcpy(old_directory, "OLDPWD", ft_strlen("OLDPWD"));
	create_or_update_env_node(env_list, old_directory, sol);
	return (0);
}

int	change_directory(char *directory)
{
	if (directory == NULL)
	{
		perror("No se pudo obtener el directorio");
		return (-1);
	}
	if (chdir(directory) == -1)
	{
		perror("Error al cambiar al directorio");
		return (-1);
	}
	return (0);
}

char	*expand_tilde(char *path) 
{
	char	*expanded_path;
	size_t	expanded_size;

	if (getenv("HOME") == NULL)
	{
		perror("No se pudo obtener el directorio");
		return (NULL);
	}
	expanded_size = ft_strlen(getenv("HOME")) + ft_strlen(path);
	expanded_path = malloc(expanded_size * sizeof(char));
	ft_strlcpy(expanded_path, getenv("HOME"), expanded_size);
	ft_strlcat(expanded_path, path + 1, expanded_size);
	return (expanded_path);
}

int	ft_cd(char **arguments, t_list *env_list)
{
	char	*home_directory;
	char	*tilde_directory;
	char	*save_old_directory;
	int		error;

	error = 0;
	home_directory = getenv("HOME");
	save_old_directory = getcwd(NULL, 0);
	if (arguments[1] == NULL)
		error = change_directory(home_directory);
	else if (arguments[1][0] != '\0' && arguments[1][0] == '-' && arguments[1][1] == '\0')
		error = change_directory(save_old_directory);
	else if (arguments[1][0] == '~')
	{
		tilde_directory = expand_tilde(arguments[1]);
		error = change_directory(tilde_directory);
		free(tilde_directory);
	}
	else
		error = change_directory(arguments[1]);
	if (error == 0)
		error = send_old_directory(env_list, save_old_directory);
	return (error);
}
