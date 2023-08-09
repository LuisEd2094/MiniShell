#include <libft.h>
#include <builtins.h>

int tab_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

char **ft_single_split(char const *s, char c)
{
    char **tab;
    int i;
    int j;

    tab = (char **)malloc(sizeof(char *) * 2);
    if (!tab)
        return (NULL);
    i = 0;
    while (s[i] && s[i] != c)
        i++;
    tab[0] = (char *)malloc(sizeof(char) * (i + 1));
    j = i;
    while(s[i])
        i++;
    //printf("%i\n", (i - j) + 1);
    tab[1] = (char *)malloc(sizeof(char) * ((i - j) + 1));
    i = 0;
    while (i < j)
    {
        tab[0][i] = s[i];
        i++;
    }
    tab[0][i] = '\0';
    i = 0;
    //printf("i=%i j=%i\n", i,j);
    while(s[j])
    {
        j++;
        tab[1][i] = s[j];
        i++;

       // printf("HOLA i=%i j=%i\n", i, j);
    }
    tab[1][i] = '\0';
    //printf("[%c]\n", tab[1][i]);
    return (tab);
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
            temp = env_list->last;
            env_node = create_env(str);
            new = ft_lstnew(env_node);
            temp->next = new;
            env_list->last = new;
        }
        else
            ((t_env *)(temp->content))->value = tab[1];
    }
}