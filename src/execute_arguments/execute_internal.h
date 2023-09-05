#ifndef EXECUTE_INTERNAL_H
# define EXECUTE_INTERNAL_H
# include <errno.h>
# include <libft.h>
# include <minishell.h>
typedef enum s_redir_type
{
    INPUT_REDIRECT = 1,
    HERE_DOCUMENT,
    OUTPUT_REDIRECT,
    APPEND_OUTPUT,

} t_redir_type;

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
int     get_white_space_size(char *input);
int     get_arg_size_skip_redirections(char *input);
int     get_redirection_size(char *input);
int     add_size_of_pipe(char *input, int * i);
int     close_redirections(t_minishell *mini);
int     check_and_handle_redirections(t_minishell *mini, int start, int end);
int     get_starting_pos(char *input);
int     get_redir_type(char *input);
char    *get_file_name(char *input, int *i);
char    *get_quoted_arg(char *input, int *start, t_minishell *mini);



char **i_just_want_to_see(t_minishell *mini);

/// new functions ///

char ***get_cmds_value(char * input);
int get_cmds_number(char *input);
int get_argument_count(char *cmd);



#endif