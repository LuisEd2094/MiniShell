#include <minishell.h>

bool compare_cmds(char *cmd, char *to_compare)
{
    if (ft_strncmp(cmd, to_compare, ft_strlen(to_compare)) \
        == 0)
        return (1);
    return (0);
}


void execute_cmds(char **cmds, t_list *env_list)
{

    if (compare_cmds(cmds[0], "env"))
        print_all_env(env_list);
    else if (compare_cmds(cmds[0], "export"))
        work_on_export(env_list, cmds[1]);
    else if (compare_cmds(cmds[0], "unset"))
        work_on_unset(env_list, cmds[1]);
    else
        try_execve(cmds, env_list);
    exit(1);    
}