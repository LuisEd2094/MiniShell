#include <libft.h>

int print_error(char *err_description, int err_value)
{
    write(STDERR_FILENO, err_description, ft_strlen(err_description));
    return (err_value);
}