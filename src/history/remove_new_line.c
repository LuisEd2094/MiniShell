
void remove_new_line(char *line)
{
    int i;
    
    i = 0;
    while (line[i] != '\n' && line[i])
        i++;
    line[i] = '\0';
}