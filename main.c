#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./includes/libft.h"
#include "history.h"


static void remove_new_line(char *line)
{
    int i;
    
    i = 0;
    while (line[i] != '\n' && line[i])
        i++;
    line[i] = '\0';
}

static t_list    *ft_read_history(int fd, t_list ** head, int *size)
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

static void add_to_history(t_list *node)
{
    t_list *temp;

    temp = node;
    while (temp)
    {
        add_history(temp->content);
        temp = temp->next;
    }
}


static t_list *get_max_input(t_list *head, int size)
{
    t_list *temp;
    int i;

    i = size - MAX_H_SIZE;
    temp = head;
    while (i-- >= 1)
        temp = temp->next;
    return (temp);
}

void update_history(t_list **head, char * input, int *size)
{
    t_list *new;

    remove_new_line(input);
    new = ft_lstnew(input);
    if (!new)
        exit(1);
    if (!(*head))
    {
        *head = new;
        (*head)->last = new;
    }
    else 
    {
        (*head)->last->next = new;
        (*head)->last = new;
    }
    *(size) += 1;
    add_history(input);
}

void work_history(int order, char *input)
{
    static t_list *head = NULL;
    static int  size = 0;

    if (order == INIT)
    {
        ft_read_history(open(HISTORY_FILE, O_RDONLY), &head, &size);
        if (size > MAX_H_SIZE)
            add_to_history(get_max_input(head, size));
        else if (head)
            add_to_history(head);
    }
    else if (order = UPDATE)
    {
        update_history(&(head), input, &(size));
    }
    t_list *temp = head;
    while (temp)
    {
        printf("size %i %s %p %p\n", size, (char *)temp->content, (void *)temp, (void *)head->last);
        temp = temp->next;
    }
  /*  t_list *temp = max_input;
    while (temp)
    {
        printf("%p %s\n",&(temp->next),  (char *)temp->content);
    }
*/
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