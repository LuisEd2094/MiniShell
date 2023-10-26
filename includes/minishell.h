/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:06:03 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 11:08:25 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <builtins.h>
# include <history.h>
# include <libft.h>
# include <execve.h>
# include <signals_mini.h>
# include <shared.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termios.h>

typedef struct s_minishell
{
	t_list			*env_list;
	char			***cmds;
	char			*input;
	int				code_here_doc;
	int				**pipes;
	int				og_in;
	int				og_out;
	int				exit_code;
	int				input_code;
	int				here_doc_number;
	char			here_doc_name[200];
	char			*here_doc_end;
	bool			here_quotes;
	pid_t			last_pid;
	struct termios	old;
	struct termios	new;
}	t_minishell;

# define TEMP_FILE_NAME "/tmp/mini_temp_"

int		g_received_signal;

void	free_cmds(char ***cmds);
int		exit_mini(t_minishell *mini);
void	prep_mini(t_minishell *mini);
void	init_mini(t_minishell *mini, char **env);
char	***get_cmds_value(char *input);
int		execute_cmds(char **cmds, t_list *env_list, \
		t_minishell *mini);
int		create_here_doc(t_minishell *mini);
void	delete_temp_files(t_minishell *mini);

int		check_and_handle_redirections(char *redir, char *file, \
		t_minishell *mini);
int		handle_redirection(char *redirection, char *file_name);

int		close_redirections(t_minishell *mini);

int		ft_pipe(char ***commands, int num_pipes, t_minishell *mini);

void	start_execute_cmds(t_minishell *mini);

int		ft_unset(char **cmds, t_minishell *mini);
int		ft_exit(char **cmd, t_minishell	*mini);

int		parse_input(char *input);
void	free_env_node(t_env *env_node);

int		check_quotes_and_env_and_redirections(char **cmd, t_minishell *mini);
void	*check_shlvl(t_list	*env_list);
void	*check_pwd(t_list	*env_list);
void	remove_node(char *str, t_minishell *mini);

void	reset_terminal(t_minishell *mini);
void	prep_terminal(t_minishell *mini);

int		close_redirections(t_minishell *mini);
int		check_number_of_here(char **cmd);

#endif
