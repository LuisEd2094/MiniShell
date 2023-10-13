/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:09:42 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 11:10:04 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <stdbool.h>

int		get_next_word_len(char *cmd);
int		get_quotes_size(char *input);
int		get_arg_size_skip_redirections(char *input);

int		get_redirection_size(char *input);
int		is_ascii_no_space(char c);
char	*ft_replace(char *cmd, char *env, int i, bool found);
void	*create_or_update_env_node(t_list *env_list, char *var, char *value);
void	free_node(t_list *temp);
void	*print_perror(void);
int		print_error(char *err_description, int err_value);
int		get_white_space_size(char *input);
char	*get_next_word(char *cmd);
char	*replace_env(char *cmd, t_list *env_list, int j);
char	*get_env_str_from_quote(char *cmd, t_list *env_list);

#endif
