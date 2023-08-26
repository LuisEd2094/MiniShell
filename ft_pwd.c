#include "direccion"

int	ft_pwd(char **arguments)
{
	char *current_directory;

	current_directory = getcwd(NULL, 0);
	if (arguments == NULL)
		return -1;
	if (current_directory == NULL)
	{
		perror("Error al obtener el directorio actual");
		return -1;
	}
	ft_printf("%s\n", current_directory);
	free(current_directory);
	return 0;
}
