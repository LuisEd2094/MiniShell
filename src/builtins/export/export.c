#include <builtins.h>

static void    free_tab_export(char **tab)
{
    free(tab[0]);
    free(tab[1]);
    free(tab);
}

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
        {
            free(((t_env *)(temp->content))->value);
            ((t_env *)(temp->content))->value = (char *)malloc(sizeof(char) * (ft_strlen(tab[1]) + 1));
            ft_strlcpy(((t_env *)(temp->content))->value, tab[1], ft_strlen(tab[1]) + 1);
            if (has_equal(str))
                ((t_env *)(temp->content))->assigned = 1;
            else
                ((t_env *)(temp->content))->assigned = 0;
        }
    }
    free_tab_export(tab);
}