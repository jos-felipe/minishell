/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/26 16:08:50 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unit_print_token_list(t_token *node)
{
	while (node)
	{
		printf("%s;", node->token);
		node = node->next;
	}
}

void	mini_init(t_mini *pipex)
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
	pipex->pathname = NULL;
	pipex->token_list = NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	mini_init(&mini);
	mini.cmd_line = argv[1];
	mini_tokenizer(&mini);
	unit_print_token_list(mini.token_list);
	mini_free_token_list(&mini.token_list); 
	return (0);
}