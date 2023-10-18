#include <minishell.h>

void	reset_terminal(t_minishell *mini)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(mini->old));
}

void	prep_terminal(t_minishell *mini)
{
	tcgetattr(STDIN_FILENO, &(mini->old));
	mini->new = mini->old;
	mini->new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(mini->new));
}
