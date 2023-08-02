#include "history_internal.h"

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