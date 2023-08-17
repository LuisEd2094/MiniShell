#include <parse_arguments.h>
#include "parse_internal.h"

bool check_if_start_word(char c)
{
    char    *values_to_check;
    int     i;

    i = 0;
    values_to_check = "\"\'>< |&";
    while (values_to_check[i])
    {

        printf("%c ", values_to_check[i]);
        i++;
    }
    printf("\n");
    return (1);

}


int get_numb_cmds(char *input, int i)
{
    int j;
    int num_cmds;

    j = i;
    num_cmds = 0;
    while(input[j])
    {
        while (input[j] && ft_isspace(input[j]))
            j++;
        
    }

}



t_cmd_values *get_cmd_value(char *input, int *pos)
{
    t_cmd_values    *new_cmd;
    int             i;
    int             num_cmds;

    i = *pos;
    new_cmd = (t_cmd_values *)malloc(sizeof(t_cmd_values));
    if (!new_cmd)
        exit (1);
    num_cmds = get_numb_cmds(input, i);
}

t_list *get_cmd_list(char *input)
{
    t_list          *cmd_list;
    t_list          *temp;
    t_cmd_values    *cmd;
    int     pos;

    pos = 0;
    cmd_list = (t_list *)malloc(sizeof(t_list));
    if (!cmd_list)
        exit(1);
    int num_cmds = get_numb_cmds(input, pos);
    printf("numb_cmds [%i]\n", num_cmds);
    /*    
    temp = cmd_list;
    while (input[pos])
    {
        cmd = get_cmd_value(input, &pos);
        if (!cmd)
            exit(1);
        temp = ft_lstnew(cmd);
        if (!temp)
            exit(1);
        temp = temp->next;

*/


    printf("%s\n", input);
    return NULL;
}