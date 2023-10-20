/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:18:07 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 12:07:21 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_INTERNAL_H
# define CD_INTERNAL_H
# include <minishell.h>
# include <builtins.h>
# include <shared.h>

int		execute_change_old_dir(char *old_dir);
void	new_pwd(t_list *env_list);

#endif
