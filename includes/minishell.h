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
	int		fd_out;
	int		og_out;
	int		fd_in;
	int		og_in;
	int		err;
	int		here_doc_number;
	char	here_doc_name[200];
	char	*here_doc_end;

}	t_minishell;

# define TEMP_FILE_NAME "/tmp/mini_temp_"

int		print_error(char *err_description);
char	***get_cmds_value(char * input, t_list *env);
void	execute_cmds(char ***cmds, t_list *env_list);
void	parse_input(t_minishell *mini);
void	delete_temp_files(t_minishell *mini);
void	handle_here_document(t_minishell *mini, int i);




int		check_and_handle_redirections(char **cmds, t_minishell *mini);
int		close_redirections(t_minishell *mini);



#endif
