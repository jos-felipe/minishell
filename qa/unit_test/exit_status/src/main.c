/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/30 11:09:25 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	mini_init(t_mini *pipex)
// {

// 	pipex->path = NULL;
// 	pipex->lst_memory = NULL;
// 	pipex->status = 0;
// 	pipex->cmd_line = NULL;
// 	pipex->pathname = NULL;
// 	pipex->token_list = NULL;
// 	pipex->env_list = NULL;
// 	pipex->cmd_exec_list = NULL;
// 	pipex->syntax_error = 0;
// }

void	unit_print_exit_status(t_mini *mini)
{
	printf("%i\n", mini->status);	
}

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	mini_init(&mini);
	mini_getenv(&mini);
	mini.cmd_line = argv[1];
	mini_tokenizer(&mini);
	if (mini.syntax_error)
	{
		unit_print_exit_status(&mini);
		ft_free_trashman(ft_get_mem_address());
		ft_free_trashman_env(ft_get_mem_address_env());
		return (0);
	}
	mini_parser(&mini);
	mini_expansion(&mini);
	mini_redirect(&mini);
	mini_execute(&mini);
	unit_print_exit_status(&mini);
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	return (0);
}