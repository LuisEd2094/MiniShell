#include <libft.h>


t_list *get_env_node(t_list *env_list, char *str)
{
    t_list  *temp;
    char    content[100];
    int     i;

    temp = env_list;
    while (temp)
    {
        i = 0;
        while (((char *)temp->content)[i] && ((char *)temp->content)[i] != '=')
            i++;
        ft_strlcpy(content, (char *)temp->content, i + 1);
        printf("%s\n", content);
        if (ft_strcmp(content, str) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

void print_env(t_list *env_list)
{
    t_list *temp;

    temp = env_list;
    while (temp)
    {
        printf("%s\n", (char *)temp->content);
        temp = temp->next;
    }
}

int init_env(char **env, t_list **env_list)
{
    t_list  *tmp;
    t_list  *new;
    int     i;

    *(env_list) = ft_lstnew(env[0]);
    if (!*env_list)
        exit(1);
    (*env_list)->last = *(env_list);
    tmp = *(env_list);
    i = 1;
    while (env[i])
    {
        new = ft_lstnew(env[i]);
        if (!new)
            exit (1);
        tmp->next = new;
        (*env_list)->last = new;
        tmp = new;
        i++; 
    }
    return 0;
}
