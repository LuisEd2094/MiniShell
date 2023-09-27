#include <execve.h>
#include <builtins.h>


char * reconstruct_env(char * variable, char *  value)
{
    char    *new;
    char    *temp;


    temp = ft_strjoin(variable, "=");
    if (!temp)
        exit(1);
    new =ft_strjoin(temp, value);
    free(temp);
    if (!new)
        exit (1);
    return (new);
}

char    **conver_env_list(t_list *env_list)
{
    //need to keep track of how many elemets on list since we need to create a malloc here for it
    int i;
    t_list * temp;
    char **new;

    temp = env_list;
    i = 0;
    while (temp)
    {
        i++;
        temp = temp->next;
    }
    new = (char **)malloc(sizeof(char *) * (i + 1));
    if (!new)
        exit (1);
    i = 0;
    temp = env_list;
    while (temp)
    {
        new[i] = reconstruct_env(((t_env *)(temp->content))->variable, \
                                 ((t_env *)(temp->content))->value);
        temp = temp->next;
        i++;
    }
    new[i] = NULL;
    return (new);
}


char  **get_paths(t_list *path_node)
{
    char **tab;

    tab = ft_split(((t_env *)(path_node->content))->value, ':');
    if (!tab)
        exit (1);
    return (tab);
}

void    free_path_list(char **path_list)
{
    int i;

    i = 0;
    while (path_list[i])
        free(path_list[i++]);
    free(path_list[i]);
}


char *join_path(char *path_list, char *cmd)
{
    char *temp_path;
    char *path_name;

    temp_path = ft_strjoin(path_list, "/");
    path_name = ft_strjoin(temp_path, cmd);
    free(temp_path);
    return(path_name);
}

char *get_path_name(char **cmd, char **path_list)
{
    char    *path_name;
    int     i;
    int     found_path;

    path_name = NULL;
    i = 0;
    found_path = 0;
    while (path_list[i])
    {
        if (path_list[i][ft_strlen(path_list[i])] != '/')
            path_name = join_path(path_list[i], cmd[0]);
        else
            path_name = ft_strjoin(path_list[i], cmd[0]);
        if (!path_name)
            exit (1);
        if (access(path_name, F_OK) !=  -1 && access(path_name, X_OK) != -1)
        {
            found_path = 1;
            break;
        }
        free(path_name);
        path_name = NULL;
        i++;
    }
    free_path_list(path_list);
    return (path_name);
}

void    try_execve(char **cmd, t_list *env_list)
{
    char    **converted_env_list;
    char    *path_name;

    path_name = get_path_name(cmd, get_paths(get_env_node(env_list, "PATH")));
    if (path_name)
    {
        converted_env_list = conver_env_list(env_list);
        execve(path_name, cmd, converted_env_list);
        for (int i = 0; converted_env_list[i]; i++)
            free(converted_env_list[i]);
    }
    else
        printf("minishell: %s: command not found\n", cmd[0]);
    if (path_name)
        free (path_name);
    return ;
}