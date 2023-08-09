#include <minishell.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
    char        *input;
    t_minishell mini;
    
    int         i = 0;


    mini.env_list = init_env(env);
    // Read previous history from a file
    work_history(INIT, NULL);

    while (i++ < 5) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            printf("\n");
            break;
        }

        if (input[0] != '\0') 
        {
            work_history(UPDATE, input);

            // Using tab here to split input using spaces
            char ** tab = ft_split(input, ' ');
            if (ft_strcmp(tab[0], "env") == 0)
                print_all_env(mini.env_list);
            if (ft_strcmp(tab[0], "export") == 0)
            {
                if (tab[1] != NULL)
                {
                    work_on_export(mini.env_list, tab[1]);
                }
                else
                {
                    work_on_export(mini.env_list, NULL);
                }
            }
        }
        printf("You entered: %s\n", input);

        free(input);
    }

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return (0);
}