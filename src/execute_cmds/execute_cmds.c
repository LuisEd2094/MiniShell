#include <minishell.h>

bool compare_cmds(char *cmd, char *to_compare)
{
    if (ft_strncmp(cmd, to_compare, ft_strlen(to_compare)) \
        == 0)
        return (1);
    return (0);
}

bool    is_built_in(char **cmds)
{
    if (compare_cmds(cmds[0], "env"))
        return (1);
    else if (compare_cmds(cmds[0], "export"))
        return (1);
    else if (compare_cmds(cmds[0], "unset"))
        return (1);
    else if (compare_cmds(cmds[0], "pwd"))
        return (1);
    else if (compare_cmds(cmds[0], "echo"))
        return (1);
    else if (compare_cmds(cmds[0], "cd"))
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
    else if (compare_cmds(cmds[0], "pwd"))
        ft_pwd(cmds);
    else if (compare_cmds(cmds[0], "echo"))
        ft_echo(cmds);
    else if (compare_cmds(cmds[0], "cd"))
        ft_cd(cmds);
    else
        try_execve(cmds, env_list);
}

void start_execute_cmds(t_minishell *mini)
{
    int num_pipes;

    num_pipes = 0;
    while (mini->cmds[num_pipes])
        num_pipes++;
    if (num_pipes > 1)
        ft_pipe(mini->cmds, num_pipes, mini);
    else if (num_pipes == 1)
    {
        if (is_built_in(mini->cmds[0]))
            execute_cmds(mini->cmds[0], mini->env_list);
        else
            ft_pipe(mini->cmds, num_pipes, mini);
    }
}