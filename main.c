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
    while (line[i] != '\n' && line[i])
        i++;
    line[i] = '\0';
}

t_list    *ft_read_history(int fd, t_list ** head, int *size)
{
    t_list  *tmp;
    t_list  *new;
    char    *line;

    if (fd <= 0)
        return NULL;
    line = get_next_line(fd, 10);
    if (line)
    {
        remove_new_line(line);
        *(head) = ft_lstnew(line); // need to check line?
        if (!*head)
            exit(1);
        *(size) += 1;
    }
    tmp = *head;
    while(line)
    {
        line = get_next_line(fd, 10);
        if (line)
        {
            remove_new_line(line);
            new = ft_lstnew(line);
            //printf("TEMPS %s\n", (char *)tmp->content);
            if (!new)
                exit(0);
            *(size) += 1;
            tmp->next = new;
            (*head)->last = new; 
            tmp = new;
        }
    }
    close(fd);
}

void add_to_history(t_list *node)
{
    t_list *temp;

    temp = node;
    while (temp)
    {
        add_history(temp->content);
        temp = temp->next;
    }
}


void    get_max_input(t_list *head, t_list **max_input, int size)
{
    t_list *temp;
    int i;

    i = size - MAX_H_SIZE;
    printf("%i\n", i);
    temp = head;
    while (i-- >= 1)
        temp = temp->next;
    printf("%i %s\n", i, (char *)temp->content);
    *(max_input) = temp;
}

void work_history(int order, char *input)
{
    static t_list *head = NULL;
    static t_list *max_input = NULL;
    static int  size = 0;

    if (order == INIT)
    {
        ft_read_history(open(HISTORY_FILE, O_RDONLY), &head, &size);
        printf("size %i\n", size);
        if (size > MAX_H_SIZE)
            get_max_input(head, &max_input, size);
        if (max_input)
            add_to_history(max_input);
        else if (head)
            add_to_history(head);
    }
    else if (order = UPDATE)
    {

    }
    //history.head->next = ft_lstnew("adios");




    /*
    t_list *temp = head;
    while (temp)
    {
        printf("size %i %s\n", size, (char *)temp->content);
        temp = temp->next;
    }
    temp = max_input;
    while (temp)
    {
        printf("%p %s\n",&(temp->content),  (char *)temp->content);
        temp = temp->next;
    }
    printf("LAST %p %s\n",&(head->last->content), (char *)head->last->content);*/
}

int main() {
    char* input;
    HISTORY_STATE *myhist;

    // Readline setup

    // Read previous history from a file
    work_history(INIT, NULL);


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
            work_history(UPDATE,input);
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