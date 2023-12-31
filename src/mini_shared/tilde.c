/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:50:32 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/23 12:08:17 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_tilde(char *path)
{
	char	*expanded_path;
	size_t	expanded_size;

	if (getenv("HOME") == NULL)
	{
		print_error("minishell: ~: Cannot set HOME\n", 0);
		return (path);
	}
	expanded_size = ft_strlen(getenv("HOME")) + ft_strlen(path) + 1;
	expanded_path = malloc(expanded_size * sizeof(char));
	ft_strlcpy(expanded_path, getenv("HOME"), expanded_size);
	if (path)
		ft_strlcat(expanded_path, path + 1, expanded_size);
	free(path);
	return (expanded_path);
}
