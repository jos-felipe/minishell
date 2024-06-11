/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:23:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/11 14:30:21 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_init(t_mini *mini)
{
	mini->path = NULL;
	mini->lst_memory = NULL;
	// mini->status = 0;
	mini->cmd_line = NULL;
	mini->pathname = NULL;
	mini->token_list = NULL;
	// mini->env_list = NULL;
	mini->cmd_exec_list = NULL;
	mini->syntax_error = 0;
	mini->mini_environ = NULL;
	mini->hd_file_index = 0;
}

void	mini_trashman_collector(t_list **list_memory, void *trash)
{
	if (list_memory)
		ft_lstadd_back(list_memory, ft_lstnew(trash));
	else
		*list_memory = ft_lstnew(trash);
}

// void	mini_safe_exit(t_mini *mini)
// {
// 	clear_history();
// 	mini_trashman(ft_get_mem_address());
// 	// exit(mini->status);
// }

void	mini_ctrl_d_exit()
{
	printf("exit\n");
	clear_history();
	// mini_trashman(ft_get_mem_address());
	// mini_safe_exit(mini);	
}