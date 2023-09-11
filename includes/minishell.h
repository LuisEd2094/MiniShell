#ifndef MINISHELL_H
# define MINISHELL_H
# include <builtins.h>
# include <history.h>
# include <libft.h>
# include <execve.h>
# include <signals_mini.h>

typedef struct s_minishell
{
    t_list      *env_list;
    char        ***cmds;
    char        *input;
    int         fd_out;
    int         og_out;
    int         fd_in;
    int         og_in;
    int         err;

}   t_minishell;

int     print_error(char *err_description);
char    ***get_cmds_value(char * input, t_list *env);
void    execute_cmds(char ***cmds, t_list *env_list);




#endif