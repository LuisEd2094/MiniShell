#include "execute_internal.h"

int get_cmds_number(char *input)
{
    int     i;
    int     cmd_count;

    i = 0;
    cmd_count = 1;
    while (input [i])
    {
        if (input [i] == '|')
            cmd_count++;
        i++;
    }
    return (cmd_count);
}