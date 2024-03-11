#include "../include/minishell.h"
#include "../include/pipex.h"

void	mini_init(t_pipex *pipex)
{
	pipex->infile = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->outfile = NULL;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->fd_pipe[0] = -1;
	pipex->fd_pipe[1] = -1;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
	pipex->path = NULL;
	pipex->argv1 = NULL;
	pipex->argv2 = NULL;
	pipex->fn1 = NULL;
	pipex->fn2 = NULL;
	pipex->lst_memory = NULL;
	pipex->status = 0;
	pipex->cmd_line = NULL;
	pipex->split_cmd_line = NULL;
	pipex->pathname = NULL;
}

void	mini_safe_exit(t_pipex *mini)
{
	mini_trashman(mini->lst_memory);
	exit(mini->status);
}

void	mini_prompt(t_pipex *mini)
{
	mini_ctrl_signal();
	mini->cmd_line = NULL;
	while (1)
	{
		mini->cmd_line = readline("prompt > ");
		mini_parse_readline(mini);
		if (mini->cmd_line == NULL)
		{
			printf("exit\n");
			mini_safe_exit(mini);
		}
		printf("%s", mini->pathname);
		printf("\n");
		mini_free_split(mini->split_cmd_line);
		free(mini->cmd_line);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex	mini;

	argc = 0;
	argv = NULL;
	mini_init(&mini);
	mini_process_envp(&mini, envp);
	mini_prompt(&mini);
	mini_safe_exit(&mini);
}