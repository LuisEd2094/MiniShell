#include <libft.h>

void    *free_2d_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        array[i++] = NULL;
    }
    if (array)
    {
        free(array);
        array = NULL;
    }
    return  (NULL);
}