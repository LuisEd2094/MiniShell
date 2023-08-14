#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int main(int argc, char **argv, char **env)
{
    char        *input;
    t_minishell mini;
    
    int         i = 0;

    char ** ls = (char **)malloc(sizeof(char *) * 2);
    ls[0] = "ls";
    ls[1] = NULL;
    mini.env_list = init_env(env);
    execve("/usr/bin/ls", ls, env);

    // Read previous history from a file

    //test branch
    work_history(INIT, NULL);
    while (1) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            printf("\n");
            break;
        }

        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        if (input[0] != '\0') 
        {
            work_history(UPDATE, input);
            // Using tab here to split input using spaces
            char **tab = ft_split(input, ' ');
            if (ft_strcmp(tab[0], "env") == 0)
                print_all_env(mini.env_list);
            if (ft_strcmp(tab[0], "export") == 0)
            {
                work_on_export(mini.env_list, tab[1]);
            }
            if (ft_strcmp(tab[0], "unset") == 0)
            {
                mini.env_list = work_on_unset(mini.env_list, tab[1]);
            }
            free_tab(tab);
        }
        free(input);
    }
    free_env_list(mini.env_list);

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return (0);
}