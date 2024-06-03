/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/30 11:08:10 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unit_print_array_list(t_mini *mini) // FOR DEBUG ONLY
{
	int i;

	i = 0;
	while (mini->commands[i])
	{
		debug_print_parse_list(&mini->commands[i]);
		printf("\n");	
		i++;
	}
}

// void	mini_init(t_mini *pipex)
// {
// 	pipex->lst_memory = NULL;
// 	pipex->status = 0;
// 	pipex->cmd_line = NULL;
// 	pipex->pathname = NULL;
// 	pipex->token_list = NULL;
// 	pipex->syntax_error = 0;
// }

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	mini_init(&mini);
	mini.cmd_line = argv[1];
	mini_tokenizer(&mini);
	mini_parser(&mini);
	unit_print_array_list(&mini);
	ft_free_trashman(ft_get_mem_address());
	return (0);
}