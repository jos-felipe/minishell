/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/09 15:36:42 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unit_print_array_list(t_mini *mini)
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
void	mini_init(t_mini *pipex)
{

	pipex->path = NULL;
	pipex->lst_memory = NULL;
	pipex->status = 0;
	pipex->cmd_line = NULL;
	pipex->pathname = NULL;
	pipex->token_list = NULL;
	pipex->env_list = NULL;
	pipex->syntax_error = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	mini_init(&mini);
	mini_init_env_list(&mini);
	mini.cmd_line = argv[1];
	mini_tokenizer(&mini);
	mini_parser(&mini);
	mini_expansion(&mini);
	unit_print_array_list(&mini);
	mini_free_trashman(get_mem_address());
	return (0);
}