/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:55:10 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:35:31 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char	*ft_replace(char *cmd, char *env, int i, bool found)
{
	char	*str_first_half;
	char	*str_second_half;
	char	*new;
	int		env_name_size;

 	env_name_size = get_next_word_len(&cmd [i  + 1]) + 1;
	str_first_half = ft_substr(cmd, 0, i);
	str_second_half = ft_substr(cmd, i + env_name_size, \
	ft_strlen(cmd) - (i  + env_name_size));
	new = (char *)malloc(sizeof(char) * (ft_strlen(str_first_half) + \
				ft_strlen(str_second_half) + ft_strlen(env)) + 1);
	ft_strlcpy(new, str_first_half, ft_strlen(str_first_half) + 1);
	ft_strlcat(new, env, ft_strlen(env) + ft_strlen(new) + 1);
	ft_strlcat(new, str_second_half, ft_strlen(str_second_half) + \
			ft_strlen(new) + 1);
	free(str_first_half);
	free(str_second_half);
	if (found)
		free(cmd);
	return (new);
}

char	*get_env_str_from_quote(char *cmd, t_list *env_list)
{
	char	*env_name;
	char	*to_return;

	env_name = get_next_word(cmd);
	if (!env_name)
		return (NULL);
	to_return = get_env_str(env_name, env_list);
	return (to_return);
}

char	*replace_env(char *cmd, char *env, int i)
{
	char	*temp;

	temp = ft_replace(cmd, env, i, 0);
	if (!temp)
		return (NULL);
	free(cmd);
	return (temp);
}
