#include <execve.h>
#include <builtins.h>

/*char ** ls = (char **)malloc(sizeof(char *) * 2);
ls[0] = "ls";
ls[1] = NULL;

execve("/usr/bin/ls", ls, env);*/

char * reconstruct_env(char * variable, char *  value)
{
    char    *new;
    char    *temp;


    temp = ft_strjoin(variable, "=");
    if (!temp)
        exit(1);
    new     =ft_strjoin(temp, value);
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

    temp = env_list;
    i = 0;
    while (temp)
    {
        i++;
        temp = temp->next;
    }
    char **new;

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

void    try_execve(char **cmd, t_list *env_list)
{
    char    **path_list;
    char    **converted_env_list;
    char    *pathname;
    char    *temp_path;
    bool    found_path;
    int     i;

    path_list = get_paths(get_env_node(env_list, "PATH"));
    i = 0;
    found_path = 0;
    while (path_list[i])
    {
        if (path_list[i][ft_strlen(path_list[i])] != '/')
        {
            temp_path = ft_strjoin(path_list[i], "/");
            pathname = ft_strjoin(temp_path, cmd[0]);
            free(temp_path);
        }
        else
            pathname = ft_strjoin(path_list[i], cmd[0]);
        if (!pathname)
            exit (1);
        if (access(pathname, F_OK) !=  -1 && access(pathname, X_OK) != -1)
        {
            found_path = 1;
            break;
        }
        if (path_list[i + 1])
            free(pathname);
        i++;
    }
    if (found_path)
    {
        converted_env_list = conver_env_list(env_list);
        execve(pathname, cmd, converted_env_list);
        for (int i = 0; converted_env_list[i]; i++)
            free(converted_env_list[i]);
    }
    else
        printf("minishell: %s: command not found\n", cmd[0]);
    free (pathname);
    i = 0;
    while (path_list[i])
        free(path_list[i++]);
    free(path_list[i]);
    return ;
}