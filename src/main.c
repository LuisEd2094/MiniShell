#include <history.h>
#include <builtins.h>
#include <stdlib.h>


int main(int argc, char **argv, char **env) {
    char* input;

    t_list *env_list;
    // Readline setup
    init_env(env, &env_list);

    // Read previous history from a file
    work_history(INIT, NULL);
    int i = 0;


    // Main loop
    while (i++ < 3) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            // NULL input indicates EOF or an error (e.g., Ctrl+D)
            printf("\n");
            break;
        }

        if (input[0] != '\0') {
            // If the input is not empty, add it to the history
            work_history(UPDATE, input);
            char ** tab = ft_split(input, ' ');
            if (ft_strcmp(tab[0], "env") == 0)
                print_env(env_list);
            
            if (ft_strcmp(tab[0], "export") == 0 && tab[1])
            {

                t_list *temp = get_env_node(env_list, tab[1]);
                if (temp)
                    
                    printf("%s\n", (char *)temp->content);
            }
            // TODO ESTO DEBE DE ESTAR EN UNA FUNCION APROXIMADAMENTE;
            // TOMAR EL NOMBRE DEL PROGRAMA; TOMAR LOS ARGUMENTS PARA EL PROGRAMA
            /*
            char **tab = ft_split(input, ' ');
            int len = 0;
            for (int i = 0; tab[i]; i++)
                len++;
            char ** arguments = malloc(sizeof(char *) *len - 1);
            for (int i = 1, j = 0; tab[i]; i++, j++)
                arguments[j] = tab[i];
            for (int i = 0; arguments[i]; i++)
                printf("%s\n", arguments[i]);*/
            /*char * env = getenv("OLDPWD");
            printf("%s\n", env);
            ft_strlcpy(env, "hola", 5);
            printf("%s\n", env);*/
        }

        // Your processing logic here...
        printf("You entered: %s\n", input);

        free(input); // Free the memory allocated by readline
    }

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return 0;
}