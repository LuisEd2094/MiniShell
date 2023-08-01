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
        (*head)->last = *(head);
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
                exit(1);
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

char *malloc_content(char *input)
{
    int i;
    char *new;
    
    i = 0;
    while (input[i])
        i++;
    new = (char *)malloc(sizeof(char) * i);
    if (!new)
        exit(1);
    i = 0;
    while (new[i])
    {
        new[i] = input[i];
        i++;
    }
    return (new);
    
}

void update_history(t_list **head, char * input, int *size)
{
    t_list  *new;
    t_list  *temp;
    char    *content;

    remove_new_line(input);
    content = malloc_content(input);
    new = ft_lstnew(content);
    printf("new contenct address %p\n",(void *)new->content);
    if (!new)
        exit(1);
    if (*(size) == 0)
    {
        *head = new;
        (*head)->last = new;
    }
    else 
    {
        temp = (*head)->last;
        temp->next = new;
        (*head)->last = new;
    }
    *(size) += 1;
    add_history(input);
}

void close_history(t_list *head, int size, int fd)
{
    t_list *temp;

    temp = head;
    printf("%s\n", (char *)head->next->content);
    while (temp)
    {
        printf("%s\n", (char *)(temp->content));
        ft_putendl_fd((char *)(temp->content), fd);
        temp = temp->next;
    }
    close(fd);

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
    else if (order == UPDATE)
        update_history(&(head), input, &(size));
    else if (order == CLOSE)
        close_history(head, size, open(HISTORY_FILE, O_WRONLY));








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

    // Readline setup

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
        }

        // Your processing logic here...
        printf("You entered: %s\n", input);

        free(input); // Free the memory allocated by readline
    }

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return 0;
}