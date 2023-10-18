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
	int		start;

	new = "";
	new = ft_strjoin(new, cmd);
	start = i;
	i++;
	free(cmd);
	printf("new value [%s] \n", new);
	while (new[i] && new[i] != '"')
	{
		if (new[i] == '$' && new[i + 1] && is_ascii_no_space(new[i + 1]) \
		&& (new[i + 1] != '"' && new[i + 1] != '\''))
		{
			env = get_env_str(get_next_word(&new[i + 1]), env_list);
			printf("before replace [%s]\n", new);
			new = ft_replace(new, env, i, 1);
			printf("after replace [%s]\n", new);
			i += ft_strlen(env);
			free(env);
		}
		i++;
	}
	printf("beofre remove[%s]\n", new);
	new = remove_quote(new, start, '"');
	return (new);
}
