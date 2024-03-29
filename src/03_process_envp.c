/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_process_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:11:53 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/29 13:14:21 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_process_envp(t_mini *mini, char *envp[])
{
	mini->path = mini_get_path(envp);
	if (mini->path == NULL)
	{
		ft_printf("PATH not found\n");
		mini->status = EXIT_FAILURE;
		mini_safe_exit(mini);
	}
	//mini_trashman_collector(&mini->lst_memory, mini->path);
	if (get_mem_address() == NULL)
	{
		ft_printf("Memory allocation failed: new list.\n");
		mini->status = EXIT_FAILURE;
		mini_safe_exit(mini);
	}
}

// void	mini_execute(t_mini *mini)
// {
// 	if (!mini->pathname)
// 		return ;
// 	mini->pid1 = fork();
// 	if (mini->pid1 < 0)
// 		mini_safe_exit(mini);
// 	if (mini->pid1 == 0)
// 		execve(mini->pathname, mini->split_cmd_line, NULL);
// }
