#ifndef EXECUTE_INTERNAL_H
# define EXECUTE_INTERNAL_H
# include <errno.h>
# include <libft.h>
# include <minishell.h>


typedef struct s_quote
{
    char    *new;
    char    *env;
    char    quote;
    int     size_new;
    int     size_temp;
    int     i;
    int     j;
}t_quote;


int     get_quotes_size(char *input);
int     get_arg_size_skip_redirections(char *input);
int     get_redirection_size(char *input);
int     add_size_of_pipe(char *input, int * i);
int     close_redirections(t_minishell *mini);
int     check_and_handle_redirections(t_minishell *mini, int start, int end);
int     get_starting_pos(char *input);
int     get_redir_type(char *input);
char    *get_file_name(char *input, int *i);



char **i_just_want_to_see(t_minishell *mini);

/// new functions ///

char ***get_cmds_value(char * input, t_list *env);
char **get_cmd_argument(char * cmd, t_list *env);
int get_cmds_number(char *input);
int get_argument_count(char *cmd);
int is_ascii_no_space(char c);


int get_white_space_size(char *input);
char *get_double_quote(char *cmd, t_list *env_list);
int    get_redirection_size(char *input);
int get_argument_len(char *cmd);
int move_start(char *cmd);


char *replace_env(char *cmd, t_list *env_list, int j);
char *ft_replace(char *cmd, char *env, int i, bool found);

char *get_env_str_from_quote(char *cmd, t_list *env_list);


char *get_next_word(char *cmd);
int get_next_word_len(char *cmd);









#endif