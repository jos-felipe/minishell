/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/30 11:07:43 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	//printf("%d", mini.syntax_error);
	ft_free_trashman(ft_get_mem_address());
	//mini_free_token_list(&mini.token_list); 
	return (0);
}