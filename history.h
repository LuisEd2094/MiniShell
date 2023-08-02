#ifndef HISTORY_H
# define HISTORY_H
# include "./includes/libft.h"

typedef struct s_history
{
    t_list *head;
    t_list *max_current_history;
} t_history;

typedef enum s_order
{
    INIT,
    UPDATE,
    CLOSE,

} h_order;

# define MAX_H_SIZE 1000
# define HISTORY_FILE "my_history.txt"

#endif