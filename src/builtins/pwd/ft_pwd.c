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

int	ft_pwd(char **arguments, t_list *env_list)
{
	char	*current_directory;
	char	*temp;

	if (arguments == NULL)
		return (-1);
	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		temp = "";
		temp = ft_strjoin(temp, "PWD");
		current_directory = get_env_str(temp, env_list);
	}
	ft_printf("%s\n", current_directory);
	free(current_directory);
	return (0);
}
