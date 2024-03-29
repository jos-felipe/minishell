/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:10:40 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/29 17:50:27 by gfantoni         ###   ########.fr       */
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
	pipex->state = 0;
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
	mini_trashman(get_mem_address());
	exit(mini->status);
}
