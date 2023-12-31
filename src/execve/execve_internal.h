/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:55:51 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 14:05:44 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_INTERNAL_H
# define EXECVE_INTERNAL_H

# include <stdlib.h>
# include <libft.h>
# include <shared.h>
# include <execve.h>
# include <builtins.h>
# include <stdbool.h>

char	*join_path(char *path_list, char *cmd);
char	*reconstruct_env(char	*variable, char	*value);
int		get_env_list_size(t_list *env_list);
void	*no_list(void);
int		no_path_name_found(char *cmd, int is_dir);
char	*check_path_name(char **cmd, t_list *env_list, int *is_dir);

#endif
