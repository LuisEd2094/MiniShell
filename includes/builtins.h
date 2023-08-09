#ifndef BUILTINS_H
# define BUILTINS_H


typedef struct s_env
{
    char    *variable;
    char    *value;
} t_env;

int init_env(char **env, t_list **env_list);
void print_env(t_list *env_list);
t_list *get_env_node(t_list *env_list, char *str);


#endif