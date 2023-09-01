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
    
    mini.env_list = init_env(env);
    // Read previous history from a file

    //test branch
    mini.env_list = init_env(env);
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
            // here we should filter the input, we should make sure that each value inside tab corresponds to a part of the command to be executed
            // so if we run something like ls -la | grep Make
            // we should have ls, -la, |, grep, Make 
            // and something like ls>>text.txt
            // should give us ls, >>, text.txt, so we can later work on each part 
            // like wise, if one of the params is calling to check an env, such as $PATH, we we filter it we should store the expanded value intabs, 
            // so echo $PATH should become echo, (what ever value path has)
            char **tab = ft_split(input, ' '); 
            if (ft_strcmp(tab[0], "env") == 0)
                print_all_env(mini.env_list);
            else if (ft_strcmp(tab[0], "export") == 0)
            {
                work_on_export(mini.env_list, tab[1]);
            }
            else if (ft_strcmp(tab[0], "unset") == 0)
            {
                mini.env_list = work_on_unset(mini.env_list, tab[1]);
            }
            else
                try_execve(tab, mini.env_list);
            free_tab(tab);
        }
        free(input);
    }
    free_env_list(mini.env_list);

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return (0);
}