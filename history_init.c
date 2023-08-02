#include "history.h"

t_list    *ft_read_history(int fd, t_list ** head, int *size)
{
    t_list  *tmp;
    t_list  *new;
    char    *line;

    if (fd <= 0)
        return (NULL);
    line = get_next_line(fd, 10);
    if (!line)
        return (NULL);
    remove_new_line(line);
    *(head) = ft_lstnew(line); // need to check line?
    if (!*head)
        exit(1);
    *(size) += 1;
    (*head)->last = *(head);
    tmp = *(head);
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