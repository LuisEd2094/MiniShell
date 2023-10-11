/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:57:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:26:02 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ARGUMENTS_INTERNAL_H
# define GET_ARGUMENTS_INTERNAL_H
# include <errno.h>
# include <libft.h>
# include <minishell.h>
# include <shared.h>


/// new functions ///

char	**get_cmd_argument(char *cmd);
char	*get_double_quote(char *cmd, t_list *env_list);

char	*replace_env(char *cmd, t_list *env_list, int j);
char	*ft_replace(char *cmd, char *env, int i, bool found);

char	*get_env_str_from_quote(char *cmd, t_list *env_list);

char	*get_next_word(char *cmd);
int		get_next_word_len(char *cmd);
int		get_argument_count(char *cmd);
char    **ft_commands_split(char *input);
int     ft_commands_count(char *input);
int     get_cmd_count(char **cmds);





#endif