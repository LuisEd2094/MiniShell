#include <minishell.h>
#include <stdlib.h>

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


    mini.env_list = init_env(env);
    // Read previous history from a file
    work_history(INIT, NULL);

    while (1) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            printf("\n");
            break;
        }

        if (ft_strcmp(input, "exit") == 0)
            exit(0);


        if (input[0] != '\0') 
        {
            work_history(UPDATE, input);

            // Using tab here to split input using spaces
            char ** tab = ft_split(input, ' ');
            if (ft_strcmp(tab[0], "env") == 0)
                print_all_env(mini.env_list);
            if (ft_strcmp(tab[0], "export") == 0)
            {
                work_on_export(mini.env_list, tab[1]);
            }
            if (ft_strcmp(tab[0], "unset") == 0)
            {
                work_on_unset(mini.env_list, tab[1]);
                continue;
            }

            free_tab(tab);


        }
        printf("You entered: %s\n", input);

        free(input);
    }

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return (0);
}