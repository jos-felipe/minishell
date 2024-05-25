/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_mini_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:23:06 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/25 17:58:23 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>

void	mini_execve(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	
	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		cmd_exec_node->pid = fork();
		if (cmd_exec_node->pid == 0)
			mini_execve_child(mini, cmd_exec_node);
		// mini_close_pipe_node_fd(cmd_exec_node);
		cmd_exec_node = cmd_exec_node->next;
	}
	mini_close_all_fd(mini);
	mini_wait_childs(mini);
	// waitpid(pid, &mini->status, 0);
}

void	mini_close_pipes(t_mini *mini, t_cmd *current)
{
	t_cmd *tmp;

	tmp = mini->cmd_exec_list;
	while(tmp)
	{
		if (tmp != current)
		{
			close(tmp->read_pipe);
			close(tmp->write_pipe);
		}
		tmp = tmp->next;
	}
}

void	mini_execve_child(t_mini *mini, t_cmd *cmd_exec_node)
{
	mini_close_pipes(mini, cmd_exec_node);
	mini_manage_execve_fd(cmd_exec_node);
	if (cmd_exec_node->cmd_exec)
	{
		execve(cmd_exec_node->cmd_path, cmd_exec_node->cmd_exec, mini->mini_environ);
		command_not_found_handler(mini, cmd_exec_node);
	}
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	// mini_close_node_fd(cmd_exec_node);
    exit(mini->status);
}

void	command_not_found_handler(t_mini *mini, t_cmd *cmd_exec_node)
{
	if (ft_strchr(cmd_exec_node->cmd_path, '/') || cmd_exec_node->cmd_path[0] == '.')
		get_captalized_errors(mini, cmd_exec_node);
	else
	{
		ft_printf_fd(2, "%s: %s: %s\n", "minishell", cmd_exec_node->cmd_path,
			"command not found");
		mini->status = 127;
	}
}

void	get_captalized_errors(t_mini *mini, t_cmd *cmd_exec_node)
{
	int		status;
	char	*error_msg;

	if (access(cmd_exec_node->cmd_path, F_OK) < 0)
	{
		error_msg = "No such file or directory";
		status = 127;
	}
	else if (access(cmd_exec_node->cmd_path, X_OK) == 0)
	{
		error_msg = "Is a directory";
		status = 126;
	}
	else
	{
		error_msg = "Permission denied";
		status = 126;
	}
	ft_printf_fd(2, "%s: %s: %s\n", "minishell", cmd_exec_node->cmd_path, error_msg);
	mini->status = status;
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
		close(cmd_exec_node->read_pipe);
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
		close(cmd_exec_node->write_pipe);
	}
}

void	mini_exit_if_fd_neg(t_cmd *cmd_exec_node)
{
	mini_close_node_fd(cmd_exec_node);
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	exit(1);
}

void	mini_close_all_fd(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	
	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		if (cmd_exec_node->input_fd != 0)
			close(cmd_exec_node->input_fd);
		if (cmd_exec_node->output_fd != 1)
			close(cmd_exec_node->output_fd);
		if (cmd_exec_node->read_pipe != -1)
			close(cmd_exec_node->read_pipe);
		if (cmd_exec_node->write_pipe != -1)
			close(cmd_exec_node->write_pipe);
		cmd_exec_node = cmd_exec_node->next;
	}
}

void	mini_close_node_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->input_fd != -1)
		close(cmd_exec_node->input_fd);
	if (cmd_exec_node->output_fd != -1)
		close(cmd_exec_node->output_fd);
	if (cmd_exec_node->read_pipe != -1)
		close(cmd_exec_node->read_pipe);
	if (cmd_exec_node->write_pipe != -1)
		close(cmd_exec_node->write_pipe);
}

void 	mini_close_pipe_node_fd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->read_pipe != -1)
		close(cmd_exec_node->read_pipe);
	if (cmd_exec_node->write_pipe != -1)
		close(cmd_exec_node->write_pipe);
}

void   mini_wait_childs(t_mini *mini)
{
    int     status;
    t_cmd	*cmd_exec_node;

    status = 0;
	cmd_exec_node = mini->cmd_exec_list;
    while (cmd_exec_node)
    {
        waitpid(cmd_exec_node->pid, &status, 0);
        cmd_exec_node = cmd_exec_node->next;
    }
    if (WIFEXITED(status))
        mini->status = WEXITSTATUS(status);
}
