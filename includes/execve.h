#ifndef EXECVE_H
# define EXECVE_H

# include   <libft.h>
#include    <unistd.h>

void    try_execve(char **cmd, t_list *env_list);

#endif