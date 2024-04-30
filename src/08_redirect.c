/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:13:42 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/30 12:08:00 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_redirect(t_mini *mini)
{
	int		i;
	t_token	*token_node;

	i = 0;
	token_node = mini->commands[i];
	while (token_node)
	{
		mini_find_redirect(mini, i);
		i++;
		token_node = mini->commands[i];
	}
}

void	mini_find_redirect(t_mini *mini, int i)
{
	t_cmd *redir_node;
	t_token	*token_node;
	
	redir_node = mini_redir_lstnew();
	token_node = mini->commands[i];
	while (token_node)
	{
		if (token_node->specie == OUT_REDIRECT)
			mini_handle_out_redir(redir_node, token_node->next->token);
		else if (token_node->specie == IN_REDIRECT)
			mini_handle_in_redir(redir_node, token_node->next->token);
		else if (token_node->specie == APPEND)
			mini_handle_append_redir(redir_node, token_node->next->token);
		token_node = token_node->next;
	}
	mini_redir_lstadd_back(&mini->cmd_exec_list, redir_node);
}

void	mini_handle_out_redir(t_cmd *redir_node, char *file)
{
	int fd;
	
	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->output_fd != 1)
		close(redir_node->output_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 420);
	if (fd < 0)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied", file);
	redir_node->output_fd = fd;
}

void	mini_handle_in_redir(t_cmd *redir_node, char *file)
{
	int fd;

	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->input_fd != 0)
		close(redir_node->input_fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied", file);
	redir_node->input_fd = fd;
}

void	mini_handle_append_redir(t_cmd *redir_node, char *file)
{
	int fd;

	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->output_fd != 1)
		close(redir_node->output_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 420);
	if (fd < 0)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied", file);
	redir_node->output_fd = fd;
}
