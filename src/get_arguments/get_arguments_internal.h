/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:57:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:03:18 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ARGUMENTS_INTERNAL_H
# define GET_ARGUMENTS_INTERNAL_H
# include <errno.h>
# include <libft.h>
# include <minishell.h>
# include <shared.h>

char	**get_cmd_argument(char *cmd);
int		get_argument_count(char *cmd);
char	**ft_commands_split(char *input);
int		ft_commands_count(char *input);
int		get_cmd_count(char **cmds);

#endif
