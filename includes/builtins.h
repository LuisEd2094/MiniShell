#ifndef BUILTINS_H
# define BUILTINS_H


typedef struct s_env
{
    char    *variable;
    char    *value;
} t_env;

int init_env(char **env, t_list **env_list);
void print_all_env(t_list *env_list);
t_list *get_env_node(t_list *env_list, char *str);
int work_on_export(t_list *env_list, char *str);
t_env *create_env(char *str);
char **ft_single_split(char const *s, char c);



#endif