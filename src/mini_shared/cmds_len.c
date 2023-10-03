int cmd_len(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    return (i);
}