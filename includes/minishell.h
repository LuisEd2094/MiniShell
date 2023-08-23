#ifndef MINISHELL_H
# define MINISHELL_H
# include <builtins.h>
# include <history.h>
# include <libft.h>
# include <parse_arguments.h>

typedef struct s_minishell
{
    t_list      *env_list;
    t_list      *cmd_list;
    char        *input;
    int         fd_out;
    int         fd_in;
    int         err;

}   t_minishell;

int print_error(char *err_description);


#endif