#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./includes/libft.h"


void remove_new_line(char *line)
{
    int i;
    
    i = 0;
    while (line[i] != '\n')
        i++;
    line[i] = '\0';
}

void    ft_read_history(const char *file)
{
    char    *line;
    int     fd;

    fd = open(file, O_RDONLY);
    printf("%i\n", fd);
    if (fd <= 0)
        return ;
    line = get_next_line(fd, 10);
    if (line)
    {
        remove_new_line(line);
        add_history(line);
    }
    while(line)
    {
        line = get_next_line(fd, 10);
        if (line)
        {
            remove_new_line(line);
            add_history(line);
        }
    }   
    close(fd);
}


int main() {
    char* input;
    HISTORY_STATE *myhist;

    // Readline setup
    rl_bind_key('\t', rl_complete); // Enable tab-completion

    // Read previous history from a file
    ft_read_history("my_history.txt");

    // Main loop
    while (1) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            // NULL input indicates EOF or an error (e.g., Ctrl+D)
            printf("\n");
            break;
        }

        if (input[0] != '\0') {
            // If the input is not empty, add it to the history
            add_history(input);
        }

        // Your processing logic here...
        printf("You entered: %s\n", input);

        free(input); // Free the memory allocated by readline
        break;
    }

    // Save history to a file before exiting
    write_history("my_history.txt");


    return 0;
}