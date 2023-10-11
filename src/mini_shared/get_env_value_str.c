/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:53:15 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:54:01 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_str(char *input, t_list *env_list)
{
	t_list	*env_node;
	char	*env_value;
	char	*temp;


	printf("env name [%s]\n", input);
	env_node = get_env_node(env_list, input);
	if (!env_node)
		env_value = (char *)malloc(sizeof(char) * 1);
	else
	{
		temp = ((t_env *)env_node->content)->value;
		env_value = (char *)malloc(sizeof(char) * ft_strlen(temp) + 1);
	}
	if (!env_value)
		return (NULL);
	if (!env_node)
		env_value[0] = '\0';
	else
		ft_strlcpy(env_value, temp, \
				ft_strlen(temp) + 1);
	free(input);
	return (env_value);
}
