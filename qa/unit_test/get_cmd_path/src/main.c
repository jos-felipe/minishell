/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/02 16:10:14 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	unit_print_cmd_exec_path(char *cmd_exec_path)
// {
// 	int	i;

// 	i = 0;
// 	if (cmd_exec_path)
// 	{
// 		while (cmd_exec_path[i])
// 		{
// 			printf("%s ", cmd_exec_path[i]);
// 			i++;
// 		}
// 	}
// }

void	unit_print_cmd_exec_path(t_cmd **head)
{
	t_cmd *node;

	node = *head;
	while (node)
	{
		printf("%s\n", node->cmd_path);
		node = node->next;
	}
}

void	mini_init(t_mini *pipex)
{

	pipex->path = NULL;
	pipex->lst_memory = NULL;
	pipex->status = 0;
	pipex->cmd_line = NULL;
	pipex->pathname = NULL;
	pipex->token_list = NULL;
	pipex->env_list = NULL;
	pipex->cmd_exec_list = NULL;
	pipex->syntax_error = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	mini_init(&mini);
	mini_getenv(&mini);
	mini.cmd_line = argv[1];
	mini_tokenizer(&mini);
	mini_parser(&mini);
	mini_expansion(&mini);
	mini_redirect(&mini);
	mini_execute(&mini);
	
	unit_print_cmd_exec_path(&mini.cmd_exec_list);
	ft_free_trashman(ft_get_mem_address());
	return (0);
}