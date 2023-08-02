#include "history.h"

void close_history(t_list *head, int size, int fd)
{
    t_list  *temp;
    int     i;

    temp = head;
    if (size > MAX_FILE_LOG_SIZE)
    {
        i = size - MAX_FILE_LOG_SIZE;
        while (i-- >= 1)
            temp = temp->next;
    }
    while (temp)
    {
        ft_putendl_fd((char *)(temp->content), fd);
        temp = temp->next;
    }
    close(fd);
    ft_lstclear(&(head), free);
    rl_clear_history();
}