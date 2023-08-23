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


char    **get_cmd_value(char *input, int start, int end);
int     get_quotes_size(char *input);
int     get_white_space_size(char *input);
int     get_ascii_size(char *input);
int     get_file_redirection_size(char *input);
int     add_size_of_pipe(char *input, int * i);
int     close_redirections(t_minishell *mini);
int     check_and_handle_redirections(t_minishell *mini, int start, int end);
int     get_starting_pos(char *input);
int     get_redir_type(char *input);
char    *get_file_name(char *input, int *i);





#endif