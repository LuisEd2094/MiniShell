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


    /*int file_descriptor = open("test3.txt asdads", O_RDONLY);

    if (file_descriptor == -1) {
        perror("minishell: test3.txt asdads");
        return 1;
    }*/
    /*
    int input_file = open("test.txt", O_RDONLY); // IF YOU NEED TO REAPLCE THE CONTENT LIKE IWTH ">"
    //int output_fd = open("test1.txt", O_WRONLY | O_CREAT | O_APPEND, 0644); // IF YOU NEED TO APPEND THE CONTENT LIKE WITH ">>"

    if (input_file == -1) {
        perror("open");
        return 1;
    }
    dup2(input_file, 1);/*
    output_fd = open("prueba.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (output_fd == -1) {
        perror("open");
        return 1;
    }

    printf("HOLA\n"),

    dup2(output_fd, 1);
    // Duplicate the file descriptor onto standard mini.input (0)
    dup2(file_descriptor, 0);*/

    /*char ** ls = (char **)malloc(sizeof(char *) * 2);
    ls[0] = "cat";
    ls[1] = NULL;


    execve("/usr/bin/cat", ls, env);*/


/*
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) { // Child process (cat)
        close(pipe_fd[1]);  // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
        
        char *cat_args[] = {"cat", "-e", NULL};
        execve("/usr/bin/cat", cat_args, NULL);
        
        perror("Execve failed");
        exit(EXIT_FAILURE);
    } else { // Parent process (ls)
        close(pipe_fd[0]);  // Close read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        
        // Print the information you want to pass to cat -e
        printf("This is the information that will be passed to cat -e\n");
        
        fflush(stdout); // Flush stdout before fork
        
        char *ls_args[] = {"ls", NULL};
        execve("/bin/ls", ls_args, NULL);
        
        perror("Execve failed");
        exit(EXIT_FAILURE);
    }*/
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
        mini.input = readline(">> "); // Prompt the user and read mini.input testing open quotes
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