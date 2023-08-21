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


int get_cmd_count(char *input, int i)
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



char **get_cmd_value_and_prep(char *input, int start, int end)
{
    char            **new_cmd;
    int             cmd_count;
    int             out_files_count;
    int             in_files_count;


    cmd_count = 0;
    if (input [start] == '|')
    {
        new_cmd;
        start++;
    }
    while (input[start] && start <= end)
    {
        while (ft_isspace(input[start]) && input[start])
            start++;
        if (input[start] == '>')
        {
            if (input[start + 1] == '>')
                start += 2;
            else
                start++;
            while(ft_isspace(input[start]))
                start++;
            
            /*if (input[start] == '>' && input[start + 1] == '>')
                continue;
            else
                continue;*/
            while (input[start] && ft_isascii(input[start]) && !ft_isspace(input[start]))
            {
                start++;
            }   
            continue;
        }
        if (input[start] == '|')
        {
            start++;
            continue; 
        }
        if (input[start] == '"' || input[start] == '\'')
        {
            char quote = input[start];
            start++;
            while(input[start] != quote)
            {
                printf("%c", input[start]);
                start++;
            }
            printf("\n");

            start++;
            cmd_count++;
            continue;
        }
        while (input[start] && ft_isascii(input[start]) && !ft_isspace(input[start]))
        {
            printf("%c", input[start]);
            start++;
        }   
        cmd_count++;
        printf("\n");
    }
    printf("cmd_count [%i]\n", cmd_count);
    return NULL;
}


t_list *get_cmd_list(char *input)
{
    t_list          *cmd_list;
    t_list          *temp;
    char            **cmd;
    int     i;
    int     j;

    cmd_list = (t_list *)malloc(sizeof(t_list));
    if (!cmd_list)
        exit(1);
    i = 0;
    j = 0;
    temp = cmd_list;
    while (input[i])
    {
        if (input[i] == '|' || !input[i + 1])
        {
            cmd = get_cmd_value_and_prep(input, j, i);
            j = i;
        }
        i++;
    }
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


int main(int argc, char **argv)
{
    printf("%s\n", argv[1]);
    get_cmd_list(argv[1]);
}