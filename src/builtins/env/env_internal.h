/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 11:57:22 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H
# include <builtins.h>
# include <shared.h>
# include <minishell.h>

t_list	*iter_env(char *env);
t_list	*fill_up_env_list(t_list *env_list, char **env);
t_list	*create_empty_list(void);
t_env	*create_new_env_node(char *env);
t_env   *check_shlvl(t_env	*node);


#endif
