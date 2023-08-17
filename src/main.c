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
    char        **tab;
    t_minishell mini;
    int         i = 0;

    mini.env_list = init_env(env);

/*
    int file_descriptor = open("test1.txt", O_RDONLY);

    if (file_descriptor == -1) {
        perror("open");
        return 1;
    }
    int output_fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (output_fd == -1) {
        perror("open");
        return 1;
    }

    dup2(output_fd, 1);
    // Duplicate the file descriptor onto standard input (0)
    dup2(file_descriptor, 0);

    char ** ls = (char **)malloc(sizeof(char *) * 4);
    ls[0] = "cat";
    ls[1] = NULL;
    ls[2] = NULL;
    ls[3] = NULL;

    execve("/usr/bin/cat", ls, env);*/
    // Read previous history from a file
    work_history(INIT, NULL);
    while (1) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            printf("\n");
        }
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        work_history(UPDATE, input);
        // Using tab here to split input using spaces
        tab = ft_split(input, ' ');
        for (int j = 0; tab[j]; j++)
            printf("[%s]\n", tab[j]);
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
    free(input);
    }
    free_env_list(mini.env_list);

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return (0);
}