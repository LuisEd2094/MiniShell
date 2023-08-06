#ifndef HISTORY_H
# define HISTORY_H
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_order
{
    INIT,
    UPDATE,
    CLOSE,

} h_order;

void work_history(int order, char *input); 

#endif