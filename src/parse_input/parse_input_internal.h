/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:45:50 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 14:36:09 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INPUT_INTERNAL_H
# define PARSE_INPUT_INTERNAL_H
# include <libft.h>
# include <stdbool.h>
# include <shared.h>

# define UNEXPECTED "minishell: syntax error near unexpected token "
# define QUOTES "minishell: syntax error, unclosed quote"
# define PIPES  "minishell: syntax error, unclosed pipe"

typedef struct s_input
{
	char	quote;
	char	redir_token;
	int		redir_pos;
	bool	pipe;
	bool	left_of_pipe;
	bool	redirections;
	int		return_val;
}	t_input;

void	check_quotes(t_input *checker, int i, char *input);
void	checker_redirections(t_input *checker, int i, char *input);
int		check_pipes(t_input *checker, char *input, int i);
int		print_input_error(char *str, char *error, int code);
int		check_vals(t_input *checker);

#endif
