#include "../include/minishell.h"

void	mini_prompt(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("prompt > ");
		if (!ft_strncmp(line, "stop", ft_strlen("stop")))
		{
			free(line);
			break ;
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