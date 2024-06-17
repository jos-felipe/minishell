/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:49:08 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 14:09:59 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

void	mini_exec_builtin(t_token *token_lst, t_mini *mini)
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

int	mini_is_simple_cmd(t_cmd *cmd_exec_node)
{
	if (cmd_exec_node->next)
		return (0);
	return (1);
}

t_token	*mini_exec_interface(char **cmd_exec)
{
	t_token	*token_lst;
	int		i;

	token_lst = NULL;
	i = 0;
	while (cmd_exec && cmd_exec[i])
		mini_token_lstadd_back(&token_lst, mini_token_lstnew(cmd_exec[i++], 0));
	return (token_lst);
}

int	mini_is_builtin(t_token *token_lst)
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
