#include <minishell.h>



void    parse_input(t_minishell *mini)
{
    int i;

    i = 0;
    while (mini->input[i])
    {
        if (mini->input[i] == '<' && mini->input[i + 1] == '<')
            handle_here_document(mini, i + 2 + get_white_space_size(&mini->input[i + 2]));
        i++;
    }
    mini->here_doc_number = 0;
    return; 
}