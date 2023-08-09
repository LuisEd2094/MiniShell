#include <builtins.h>

int work_on_export(t_list *env_list, char *str)
{
    char **tab;
    t_list  *temp;
    t_list  *new;
    t_env   *env_node;

    tab = NULL;
    if (str != NULL)
        tab = ft_single_split(str, '=');
    if (!tab)
        printf("Need to print export declare\n");
    else
    {
        temp = get_env_node(env_list, tab[0]);
        if (!temp)
        {
            add_new_env(env_list, str);
        }
        else
            update_env_value(((t_env *)(temp->content)), tab[1]);
    }
}