/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:55:51 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 11:55:52 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_INTERNAL_H
# define EXECVE_INTERNAL_H

# include <stdlib.h>
# include <libft.h>

char	*join_path(char *path_list, char *cmd);
char	*reconstruct_env(char	*variable, char	*value);

#endif
