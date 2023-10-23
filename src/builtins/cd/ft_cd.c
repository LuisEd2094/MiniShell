/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:50:32 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/18 12:08:17 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_internal.h"

int	change_directory(char *directory)
{
	if (directory == NULL)
	{
		print_error("minishell: cd: ", 1);
		print_error(directory, 1);
		return (print_error(": No file or directory\n", 1));
	}
	if (chdir(directory) == -1)
	{
		print_error("minishell: cd: ", 1);
		print_error(directory, 1);
		return (print_error(": No file or directory\n", 1));
	}
	return (0);
}

int	send_old_directory(t_list *env_list, char *sol)
{
	if (sol == NULL)
	{
		perror("Current directory not found: redirecting to HOME");
		change_directory(getenv("HOME"));
	}
	new_pwd(env_list);
	if (sol != NULL)
		create_or_update_env_node(env_list, "OLDPWD", sol);
	return (0);
}

int	change_old_directory(t_list *env_list)
{
	char	*old_dir;
	char	*word_od;
	int		status;

	status = 0;
	word_od = malloc((ft_strlen("OLDPWD") + 1) * sizeof(char));
	if (word_od == NULL)
	{
		return (print_error("minishell: cd: malloc() failed: \
			insufficient memory\n", 3));
	}
	ft_strlcpy(word_od, "OLDPWD", ft_strlen("OLDPWD") + 1);
	old_dir = get_env_str(word_od, env_list);
	status = execute_change_old_dir(old_dir);
	return (status);
}

char	*expand_tilde(char *path)
{
	char	*expanded_path;
	size_t	expanded_size;

	if (getenv("HOME") == NULL)
	{
		perror("minishell: cd: Cannot set HOME");
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
	else if (arguments[1][0] == '-' && arguments[1][1] == '\0')
		error = change_old_directory(env_list);
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
	free(save_old_directory);
	return (error);
}
