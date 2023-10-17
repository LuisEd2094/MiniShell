#include <shared.h>

void    prep_unset_export_commands(char **cmds)
{
    int i;

    i = -1;
    while (cmds[++i])
    {
        if (!cmds[i][0])
            remove_cmds_from_cmds(cmds, i, 1);
    }
}