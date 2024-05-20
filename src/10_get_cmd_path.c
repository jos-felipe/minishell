/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:27:24 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/20 14:29:21 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/mini_get_cmd_path.h"

void	mini_get_cmd_exec_path(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	
	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		if (cmd_exec_node->nbr_of_words)
			cmd_exec_node->cmd_path = mini_get_cmd_path(cmd_exec_node);
		cmd_exec_node = cmd_exec_node->next;
	}
}

char	*mini_get_cmd_path(t_cmd *cmd_exec_node)
{
	t_get_cmd_path tmp_struct;
	int i;

	tmp_struct.cmd_name = cmd_exec_node->cmd_exec[0];
	if (tmp_struct.cmd_name[0] == '.' && tmp_struct.cmd_name[1] == '/')
		return (tmp_struct.cmd_name);
	tmp_struct.path = getenv("PATH");
	tmp_struct.splited_path = ft_split(tmp_struct.path, ':');
	i = 0;
	while (tmp_struct.splited_path[i])
	{
		tmp_struct.part_path = ft_strjoin(tmp_struct.splited_path[i], "/");
		tmp_struct.path = ft_strjoin(tmp_struct.part_path, tmp_struct.cmd_name);
		ft_collect_mem(tmp_struct.path);
		free(tmp_struct.part_path);
		if (access(tmp_struct.path, F_OK) == 0)
		{
			mini_free_split(tmp_struct.splited_path);
			return (tmp_struct.path);
		}
		i++;
	}
	mini_free_split(tmp_struct.splited_path);
	return (tmp_struct.cmd_name);
}
