#include <libft.h>
#include <errno.h>

int print_error(char *err_description, int err_value)
{
    write(STDERR_FILENO, err_description, ft_strlen(err_description));
    return (err_value);
}

void    *print_perror(void)
{
    perror("minishell :");
    return (NULL);
}