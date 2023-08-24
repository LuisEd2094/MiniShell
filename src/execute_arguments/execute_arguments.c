#include "execute_internal.h"

int execute_input(t_minishell *mini)
{
    char    **cmd;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (mini->input[i])
    {
        if (mini->input[i] == '|' || !mini->input[i + 1])
        {
            printf("\t I am working on a new command\t\n");
            cmd = get_cmd_value(mini, j, i);
            if (!cmd)
                return (errno);
            if (!check_and_handle_redirections(mini, j, i))
                return (errno);
            //handle pipe//
            // once we get cmds, we should check if they are built ins or not, and execute the functions, I'm gonna need to get the env lists for this function 
            j = i;
            
            //check cmds to decide what to execute, if built ins or excev

            char buffer[1024];
            ssize_t bytesRead;
            if (cmd[0]  && cmd[0][0] == 'k')
            {
                execve("/usr/bin/ls", cmd, NULL);
            }
            ft_printf("GOT CMDS: \n");
            for (int k = 0; cmd[k]; k++)
            {
                ft_printf("[%s]\n", cmd[k]);
            }
            if (!close_redirections(mini))
            {
                return (errno);
            }
        }
        i++;
    }

    return (0); // should return 0 if no fail, so mini shell can save the last error,
}

int main(int argc, char **argv, char **env)
{
    t_minishell mini;

    mini.input = argv[1];
    mini.fd_out = 0;
    mini.fd_in = 1;
    mini.og_out = dup(STDOUT_FILENO);
    mini.env_list = init_env(env);
    mini.err = execute_input(&mini);
    ft_printf("%s\n", argv[1]);
    close(mini.og_in);
    close(mini.og_out);
    //execute return 0 if no error and errno if error, it should be enough for minishell.er to get that value
    // built ins might want to return a different error
}