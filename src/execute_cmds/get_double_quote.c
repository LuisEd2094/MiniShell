/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:11:38 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:12:16 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmds_internal.h"

char *get_double_quote(char *cmd, t_list *env_list)
{
    char    *new;
    char    *env;
    int     i;
    bool     found_env; 
    
    i = 0;
    found_env = 0;
    new = cmd;
    while (new[i] && new[i] != '"')
    {
        if (new[i] == '$' && new[i + 1] && is_ascii_no_space(new[i + 1]) && new[i + 1] != '"') //Leaving comment, need to check what are valid $ENV names
        {
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