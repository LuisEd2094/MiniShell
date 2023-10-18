/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:01:56 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:02:32 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmds_internal.h"

char	*get_double_quote(char *cmd, t_list *env_list, int i)
{
	char	*env;
	char	*new;

	new = "";
	new = ft_strjoin(new, cmd);
	free(cmd);
	printf("[%s]\n", &new[i]);
	while (new[i] && new[i] != '"')
	{
		if (new[i] == '$' && new[i + 1] && is_ascii_no_space(new[i + 1]) \
		&& (new[i + 1] != '"' && new[i + 1] != '\''))
		{
			printf("i am about to replace\n");
			env = get_env_str(get_next_word(&new[i + 1]), env_list);
			new = ft_replace(new, env, i, 1);
			free(env);
		}
		i++;
	}
	printf("after cycle [%s]\n", new);
	return (new);
}
