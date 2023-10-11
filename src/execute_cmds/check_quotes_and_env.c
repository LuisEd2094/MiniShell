#include "execute_cmds_internal.h"

int check_quotes_and_env(char **cmd, t_minishell *mini)
{
    int i;
    int j;

    i = 0;
    while(cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == '"')
                cmd[i] = get_double_quote(&cmd[i][j + 1], mini->env_list);
            else if (cmd[i][j] == '\'')
            {
                j++;
                while (cmd[i][j] != '\'')
                    j++;
            }
            else if (cmd[i][j] == '$' && cmd[i][j + 1] == '?')
                cmd[i] = ft_itoa(mini->exit_code);
            else if (cmd[i][j] == '$' && \
            is_ascii_no_space(cmd[i][j + 1]) && \
            cmd[i][j + 1])
                cmd[i] = replace_env(cmd[i], mini->env_list , j);
            if (!cmd[i])
                exit(1);
            j++;
        }
        i++;
    }
}