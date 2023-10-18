/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:01:28 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:01:40 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMDS_INTERNAL_H
# define EXECUTE_CMDS_INTERNAL_H  

# include <errno.h>
# include <libft.h>
# include <minishell.h>
# include <shared.h>

char	*get_double_quote(char *cmd, t_list *env_list, int i);
int     remove_quote(char *str,  char quote);


#endif
