/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_mini_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:23:06 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/08 15:55:17 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_execve(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	int		pid;
	
	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		pid = fork();
		if (pid == 0)
			mini_execve_child(cmd_exec_node);
		cmd_exec_node = cmd_exec_node->next;
	}
	mini_close_all_fd(mini);
}

void	mini_execve_child(t_cmd *cmd_exec_node)
{
	mini_manage_execve_fd(cmd_exec_node);
	if (execve(cmd_exec_node->cmd_path, cmd_exec_node->cmd_exec, NULL) == -1)
	{
        perror(NULL);
		ft_free_trashman(ft_get_mem_address());
		mini_close_node_fd(cmd_exec_node);
        exit(1);
	}
}

void	mini_manage_execve_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->input_fd < 0 || cmd_exec_node->output_fd < 0)
		mini_exit_if_fd_neg(cmd_exec_node);
	if (cmd_exec_node->input_fd > 0)
	{
		dup2(cmd_exec_node->input_fd, STDIN_FILENO);
		close(cmd_exec_node->read_pipe);
		close(cmd_exec_node->input_fd);
	}
	else if (cmd_exec_node->input_fd == 0 && cmd_exec_node->read_pipe != -1)
	{
		dup2(cmd_exec_node->read_pipe, STDIN_FILENO);
		close(cmd_exec_node->write_pipe);
	}
	if (cmd_exec_node->output_fd > 1)
	{
		dup2(cmd_exec_node->output_fd, STDOUT_FILENO);
		close(cmd_exec_node->write_pipe);
		close(cmd_exec_node->output_fd);
	}
	else if (cmd_exec_node->output_fd == 1 && cmd_exec_node->write_pipe != -1)
	{
		dup2(cmd_exec_node->write_pipe, STDOUT_FILENO);
		close(cmd_exec_node->read_pipe);
	}
}

void	mini_exit_if_fd_neg(t_cmd *cmd_exec_node)
{
	ft_free_trashman(ft_get_mem_address());
	mini_close_node_fd(cmd_exec_node);
	exit(1);
}

void	mini_close_all_fd(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	
	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		close(cmd_exec_node->input_fd);
		close(cmd_exec_node->output_fd);
		close(cmd_exec_node->read_pipe);
		close(cmd_exec_node->write_pipe);
		cmd_exec_node = cmd_exec_node->next;
	}
}

void	mini_close_node_fd(t_cmd *cmd_exec_node)
{
	close(cmd_exec_node->input_fd);
	close(cmd_exec_node->output_fd);
	close(cmd_exec_node->read_pipe);
	close(cmd_exec_node->write_pipe);
}
