#include <stdlib.h>


void	remove_cmds_from_cmds(char **cmds, int i, int next_valid)
{
	int		j;
	char	*temp;

	j = i + next_valid;
	while (cmds[j])
	{
		temp = cmds[i];
		cmds[i] = cmds[j];
		cmds[j] = temp;
		i++;
		j++;
	}
	while (i < j)
	{
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
}