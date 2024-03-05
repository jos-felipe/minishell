#include "../includes/mini_shell.h"

void sig_handler(int signum) 
{
	if (signum == SIGINT)
		printf("\nprompt > ");
	if (signum == SIGQUIT)
		;
}

void	mini_prompt(void)
{
	char	*line;

	struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

	line = NULL;
	while (1)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1) 
		{
        	perror("sigaction");
        	exit(EXIT_FAILURE);
		}
		if (sigaction(SIGQUIT, &sa, NULL) == -1) 
		{
        	perror("sigaction");
        	exit(EXIT_FAILURE);
		}
		line = readline("prompt > ");
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, 1);
		ft_putstr_fd("\n", 1);
		free(line);
	}
}

int main(void)
{
	mini_prompt();
	return (0);
}