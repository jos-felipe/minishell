/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:23:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/24 10:38:45 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_init(t_mini *pipex)
{
	pipex->path = NULL;
	pipex->lst_memory = NULL;
	pipex->status = 0;
	pipex->cmd_line = NULL;
	pipex->pathname = NULL;
	pipex->token_list = NULL;
	pipex->env_list = NULL;
	pipex->cmd_list = NULL;
	pipex->syntax_error = 0;
}

void	mini_trashman_collector(t_list **list_memory, void *trash)
{
	if (list_memory)
		ft_lstadd_back(list_memory, ft_lstnew(trash));
	else
		*list_memory = ft_lstnew(trash);
}

void	mini_safe_exit(t_mini *mini)
{
	clear_history();
	mini_trashman(ft_get_mem_address());
	exit(mini->status);
}

void	mini_ctrl_d_exit(t_mini *mini)
{
	printf("exit\n");
	mini_safe_exit(mini);	
}