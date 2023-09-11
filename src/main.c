#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

void free_cmds(char ***cmds)
{
    int i;
    int j;

    i = 0;
    while (cmds[i])
    {
        j = 0;
        while (cmds[i][j])
        {
            if (cmds[i][j])
                free(cmds[i][j]);
            j++;
        }
        free(cmds[i]);
        i++;
    }
    free(cmds);
}

int main(int argc, char **argv, char **env)
{
    char        **tab;
    t_minishell mini;
    
    mini.env_list = init_env(env);
    mini.here_doc_number = 0;
    work_history(INIT, NULL);
    while (1) {
        mini.input = readline(">> "); // Prompt the user and read mini.input testing open quotes
        if (mini.input[0] == '"' && mini.input[1] != '"')//test to check how to handle unclosed quotes
        {
            char *second_input = readline(">> ");
            printf ("first,<%s> second <%s>\n", mini.input, second_input);
        }
        if (!mini.input) {
            printf("\n");
        }
        if (ft_strcmp(mini.input, "exit") == 0)
        {
            free(mini.input);
            break;
        }
        if (mini.input[0] != '\0') 
        {
            work_history(UPDATE, mini.input);
            parse_input(&mini);
            // Using tab here to split input using spaces
            // here we should filter the input, we should make sure that each value inside tab corresponds to a part of the command to be executed
            // so if we run something like ls -la | grep Make
            // we should have ls, -la, |, grep, Make 
            // and something like ls>>text.txt
            // should give us ls, >>, text.txt, so we can later work on each part 
            // like wise, if one of the params is calling to check an env, such as $PATH, we we filter it we should store the expanded value intabs, 
            // so echo $PATH should become echo, (what ever value path has)
            mini.cmds = get_cmds_value(mini.input, mini.env_list);
            for (int i = 0; mini.cmds[i]; i++)
            {
                for (int j = 0; mini.cmds[i][j]; j++)
                    printf("cmd[%s]\n", mini.cmds[i][j]);
            }
            execute_cmds(mini.cmds, mini.env_list);
            /*
            printf("First argument of first cmd [%s]\n", mini.cmds[0][0] );
            if (mini.cmds[1] && mini.cmds[1][0] )
                printf("First argument of scd cmd [%s]\n", mini.cmds[1][0] );*/
            free_cmds(mini.cmds);
        }
        free(mini.input);
        
    }
    free_env_list(mini.env_list);
    work_history(CLOSE, NULL);
    return (0);
}