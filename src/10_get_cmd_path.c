/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:27:24 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/02 17:56:55 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	char	*cmd_name;
	char	*path;
	char	*part_path;
	char	**splited_path;
	int		i;

	cmd_name = cmd_exec_node->cmd_exec[0];
	path = getenv("PATH");
	splited_path = ft_split(path, ':');
	i = 0;
	while (splited_path[i])
	{
		part_path = ft_strjoin(splited_path[i], "/");
		path = ft_strjoin(part_path, cmd_name);
		ft_collect_mem(path);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			mini_free_split(splited_path);
			return (path);
		}
		i++;
	}
	mini_free_split(splited_path);
	return (path);
}
