#ifndef HISTORY_INTERNAL_H
# define HISTORY_INTERNAL_H
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

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

# define MAX_LOG_SIZE 1000
# define MAX_FILE_LOG_SIZE 2000
# define HISTORY_FILE "my_history.txt"

t_list    *ft_read_history(int fd, t_list ** head, int *size);
void remove_new_line(char *line);
void add_to_history(t_list *node);
void update_history(t_list **head, char *input, int *size);
void close_history(t_list *head, int size, int fd);


#endif