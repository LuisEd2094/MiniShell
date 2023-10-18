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

char	*get_double_quote(char *cmd, t_list *env_list)
{
	char	*new;
	char	*env;
	int		i;
	bool	found_env;

	found_env = 0;
	i = 0;
	new = cmd;
	printf("printf [%s]\n", cmd);
	while (new[i] && new[i] != '"')
	{
		if (new[i] == '$' && new[i + 1] && is_ascii_no_space(new[i + 1]) \
		&& !(new[i + 1] != '"' || new[i + 1] != '\''))
		{
			printf("i am about to replacer [%i] \n", new[i + 1] != '"' || new[i + 1] != '\'') ;
			env = get_env_str_from_quote(&new[i + 1], env_list);
			new = ft_replace(new, env, i, found_env);
			if (new[ft_strlen(new) - 1] == '"')
				new[ft_strlen(new) - 1] = '\0';
			free(env);
			found_env = 1;
		}
		i++;
	}
	if (!found_env)
		new = ft_substr(cmd, 0, i);
	return (new);
}
