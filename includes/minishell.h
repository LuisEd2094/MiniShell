#ifndef MINISHELL_H
# define MINISHELL_H
# include <builtins.h>
# include <history.h>
# include <libft.h>
# include <execve.h>
# include <signals_mini.h>
# include <shared.h>

typedef struct s_minishell
{
	t_list	*env_list;
	char	***cmds;
	char	*input;
	int		**pipes;
	int		exit_code;
	int		here_doc_number;
	char	here_doc_name[200];
	char	*here_doc_end;
	pid_t	last_pid;

}	t_minishell;

# define TEMP_FILE_NAME "/tmp/mini_temp_"

//mini auxs//

void	free_cmds(char ***cmds);
void	exit_mini(t_minishell *mini);
void	prep_mini(t_minishell *mini);
void	init_mini(t_minishell *mini, char **env);

char	***get_cmds_value(char * input);
int		execute_cmds(char **cmds, t_list *env_list, t_minishell *mini);
void	create_here_doc(t_minishell *mini);
void	delete_temp_files(t_minishell *mini);
void	handle_here_document(t_minishell *mini, int i);

int		check_and_handle_redirections(char **cmds, t_minishell *mini);
int		close_redirections(t_minishell *mini);

int		ft_pipe(char ***commands, int num_pipes, t_minishell *mini);

void	signal_action(void);

void	start_execute_cmds(t_minishell *mini);

int		ft_unset(t_list *env_list, char **cmds, t_minishell *mini);

int		parse_input(char *input);
void	free_env_node(t_env *env_node);

int		check_quotes_and_env(char **cmd, t_minishell *mini);





#endif
