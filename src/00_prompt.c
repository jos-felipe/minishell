#include "../include/minishell.h"

void	mini_safe_exit(int status, char *line)
{
	if (line)
		free(line);
	exit(status);
}

void	mini_prompt(void)
{
	char	*line;
	
	mini_ctrl_signal();
	line = NULL;
	while (1)
	{
		line = readline("prompt > ");
		if (line == NULL)
		{
			printf("exit\n");
			mini_safe_exit(EXIT_SUCCESS, line);
		}
		printf("%s", line);
		printf("\n");
		free(line);
	}
}

int main(void)
{
	mini_prompt();
	return (0);
}