/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_mini_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:23:06 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 11:34:34 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include "../include/builtins.h"

static int	mini_is_simple_cmd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->next)
		return (0);
	return (1);
}

static int mini_is_builtin(t_token *token_lst)
{
	char	*cmd;
	int		is_builtin;

	is_builtin = 0;
	if (!token_lst)
		return (is_builtin);
	cmd = token_lst->token;
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		is_builtin = 1;
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		is_builtin = 1;
	return (is_builtin);
}

static void mini_exec_builtin(t_token *token_lst, t_mini *mini)
{
	char	*cmd;
	t_token	*arg;

	cmd = token_lst->token;
	arg = token_lst->next;
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		mini->status = mini_export(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		mini->status = mini_echo(arg);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		mini->status = mini_pwd(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		mini->status = mini_cd(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		mini->status = mini_env(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		mini->status = mini_unset(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		mini_exit(arg, mini->status);
}

static void mini_exec_fork(t_mini *mini, t_cmd *cmd_exec_node, t_token *token_node)
{
	mini->int_action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &mini->int_action, NULL);
	cmd_exec_node->pid = fork();
	if (cmd_exec_node->pid == 0)
		mini_execve_child(mini, cmd_exec_node, token_node);
}

void	mini_execve(t_mini *mini)
{
	t_cmd	*cmd_exec_node;
	t_token *token_lst;
	int		i;
	int		is_simple_cmd;
	int		is_builtin;
	
	cmd_exec_node = mini->cmd_exec_list;
	is_simple_cmd = mini_is_simple_cmd(cmd_exec_node);
	i = 0;
	while (cmd_exec_node)
	{
		token_lst = mini_exec_interface(cmd_exec_node->cmd_exec);
		is_builtin = mini_is_builtin(token_lst);
		if (is_simple_cmd && is_builtin)
			mini_exec_builtin(token_lst, mini);
		else
			mini_exec_fork(mini, cmd_exec_node, token_lst);
		cmd_exec_node = cmd_exec_node->next;
		i++;
	}
	mini_close_all_fd(mini);
	mini_wait_childs(mini);
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

void	mini_execve_child(t_mini *mini, t_cmd *cmd_exec_node, t_token *token_node)
{
	t_token *token_lst;
	
	mini->int_action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &mini->int_action, NULL);
	mini->quit_action.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &mini->quit_action, NULL);
	mini_close_pipes(mini, cmd_exec_node);
	mini_manage_execve_fd(cmd_exec_node);
	if (cmd_exec_node->cmd_path && !mini_cmd_selection(token_node, mini))
	{
		execve(cmd_exec_node->cmd_path, cmd_exec_node->cmd_exec, mini->mini_environ);
		command_not_found_handler(mini, cmd_exec_node);
	}
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
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
static void mini_get_status(t_mini *mini, int status)
{
	if (WIFEXITED(status))
        mini->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		printf("\n");
		if (WTERMSIG(status) == SIGQUIT)
			mini->status = 131;
		else if (WTERMSIG(status) == SIGINT)
			mini->status = 130;
	}
}
void   mini_wait_childs(t_mini *mini)
{
    int     status;
	int		signal;
    t_cmd	*cmd_exec_node;

    status = 0;
	cmd_exec_node = mini->cmd_exec_list;
    while (cmd_exec_node)
    {
        waitpid(cmd_exec_node->pid, &status, 0);
		mini_get_status(mini, status);
        cmd_exec_node = cmd_exec_node->next;
    }
    // if (WIFEXITED(status))
    //     mini->status = WEXITSTATUS(status);
	// else if (WIFSIGNALED(status))
	// {
	// 	printf("\n");
	// 	if (WTERMSIG(status) == SIGQUIT)
	// 		mini->status = 131;
	// 	else if (WTERMSIG(status) == SIGINT)
	// 		mini->status = 130;
	// }
}

int	mini_cmd_selection(t_token *token_lst, t_mini *mini)
{
	char	*cmd;
	t_token	*arg;
	int		executed;

	cmd = token_lst->token;
	arg = token_lst->next;
	executed = 1;
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		mini->status = mini_export(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		mini->status = mini_echo(arg);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		mini->status = mini_pwd(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		mini->status = mini_cd(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		mini->status = mini_env(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		mini_exit(arg, mini->status);
	else
		executed = 0;
	return (executed);
}
