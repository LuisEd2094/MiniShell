#include "history_internal.h"

void update_history(t_list **head, char *input, int *size)
{
    t_list  *new;
    t_list  *temp;
    char    *content;

    if ((*head) && ft_strcmp((*head)->last->content, input) == 0)
        return ;
    remove_new_line(input);
    content = ft_strdup(input);
    if (!content)
        return ;
    new = ft_lstnew(content);
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