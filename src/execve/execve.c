#include <execve.h>
#include <builtins.h>

/*char ** ls = (char **)malloc(sizeof(char *) * 2);
ls[0] = "ls";
ls[1] = NULL;

execve("/usr/bin/ls", ls, env);*/

char  **get_paths(t_list *path_node)
{
    char **tab;

    tab = ft_split(((t_env *)(path_node->content))->value, ':');
    if (!tab)
        exit (1);
    return (tab);
}

void    try_execve(char **tab, t_list *env_list)
{
    char    **path_list;
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
            pathname = ft_strjoin(temp_path, tab[0]);
            free(temp_path);
        }
        else
            pathname = ft_strjoin(path_list[i], tab[0]);
        if (!pathname)
            exit (1);
        printf("[%s] PATHNAME\n", pathname);
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
        printf("[%s]found path\n", pathname);
    free (pathname);
    i = 0;
    while (path_list[i])
        free(path_list[i++]);
    free(path_list[i]);

    return ;
}