#include <stdlib.h>

void	free_3d_array(char ***array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j])
				free(array[i][j]);
			j++;
		}
		free(array[i]);
		i++;
	}
	free(array);
}