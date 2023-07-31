#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./includes/libft.h"
#include "history.h"


void remove_new_line(char *line)
{
    int i;
    
    i = 0;
    while (line[i] != '\n')
        i++;
    line[i] = '\0';
}

t_list    *ft_read_history(const char *file)
{
    t_list  *node;
    t_list  *tmp;
    t_list  *new;
    char    *line;
    int     fd;

    fd = open(file, O_RDONLY);
    if (fd <= 0)
        return NULL;
    line = get_next_line(fd, 10);
    if (line)
    {
        remove_new_line(line);
        node = ft_lstnew(line); // need to check line?
        if (!node)
            exit(1);
    }
    tmp = NULL;
    node->next = tmp;
    while(line)
    {
        line = get_next_line(fd, 10);
        if (line)
        {
            remove_new_line(line);
            tmp = ft_lstnew(line);
            //printf("TEMPS %s\n", (char *)tmp->content);
            if (!tmp)
                exit(0);
            tmp->next = tmp;
            tmp = tmp->next;
        }
    }
    close(fd);
    return (node);
}

void init_history()
{
    static t_list *head = NULL;
    static t_list *max_input = NULL;

    if (!head)
        head = ft_read_history("my_history.txt");
    //history.head->next = ft_lstnew("adios");

    t_list *temp = head;
    while (temp)
    {
        printf(" %s\n", (char *)temp->content);
        temp = temp->next;
    }
}

int main() {
    char* input;
    HISTORY_STATE *myhist;

    // Readline setup

    // Read previous history from a file
    init_history();


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