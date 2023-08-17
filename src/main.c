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
    // Duplicate the file descriptor onto standard mini.input (0)
    dup2(file_descriptor, 0);*/
/*
    char ** ls = (char **)malloc(sizeof(char *) * 4);
    ls[0] = "cat";
    ls[1] = "/home/luised2094/MiniShell/test.txt  /home/luised2094/MiniShell/test1.txt";
    ls[2] = NULL;
    ls[3] = NULL;

    execve("/usr/bin/cat", ls, env);*/
/*
    bool *has_;

    has_= (bool *)malloc(sizeof(bool) * 4);
    has_[0] = 0;
    has_[1] = 1;
    has_[2] = 0;
    has_[3] = NULL;


    for (int j = 0; j < 3; j++)
    {
        printf("Has pos [%i] has this value =  [%i]\n", j, has_[j]);
    }*/
    // Read previous history from a file

    //printf("%s", "hola\"");
    work_history(INIT, NULL);
    while (1) {
        mini.input = readline(">> "); // Prompt the user and read mini.input
        if (mini.input[0] == '"' && mini.input[1] != '"')
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
        work_history(UPDATE, mini.input);
        // Using tab here to split mini.input using spaces
        //mini.cmd_list = get_cmd_list(mini.input);
        tab = ft_split(mini.input, ' ');
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
        printf("<%s>\n", mini.input);
        free_tab(tab);
    free(mini.input);
    }
    free_env_list(mini.env_list);

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return (0);
}