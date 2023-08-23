#include <minishell.h>

void print_from_file(char *err_file)
{
    char buffer[100];
    int temp_file;
    int bites;
    
    temp_file = open(err_file, O_RDONLY);
    if (temp_file) 
    {
        bites = 1;
        while (bites)
        {
            bites = read(temp_file, buffer, 100);
            if (bites)
            {
                buffer[bites] = '\0';
                printf("%s", buffer);
            }
        }
    }
    close(temp_file);
    unlink(err_file);
}

int print_error(char *err_description)
{
    char    *err_file;
    int     original_stderr;
    int     temp_stderr;

    err_file = "temp_stderr.txt";
    original_stderr = dup(STDERR_FILENO);
    temp_stderr = open(err_file, O_WRONLY | O_CREAT, 0666);
    dup2(temp_stderr, STDERR_FILENO);
    printf("MiniShell: ");
    if (err_description)
        perror(err_description);
    else
        perror(NULL);
    dup2(original_stderr, STDERR_FILENO);
    close(temp_stderr);
    print_from_file(err_file);
    return (0);
}