#ifndef MINISHELL_H
# define MINISHELL_H
# include <builtins.h>
# include <history.h>
# include <libft.h>

typedef struct s_minishell
{
    t_list      *env_list;
    t_list      *cmd_list;
    char        *input;
    int         fd_out;
    int         og_out;
    int         fd_in;
    int         og_in;
    int         err;

}   t_minishell;

int print_error(char *err_description);
int execute_input(t_minishell *mini);



#endif