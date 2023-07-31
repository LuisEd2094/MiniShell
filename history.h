#ifndef HISTORY_H
# define HISTORY_H
# include "./includes/libft.h"

typedef struct s_history
{
    t_list *head;
    t_list *max_current_history;
} t_history;

#endif