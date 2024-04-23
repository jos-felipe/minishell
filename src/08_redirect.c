/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:13:42 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/23 15:16:25 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_redirect(t_mini *mini)
{
	int		i;
	t_token	*cmd;

	i = 0;
	cmd = mini->commands[i];
	while (cmd)
	{
		mini_find_redirect(mini, i);
		i++;
		cmd = mini->commands[i];
	}
}

void	mini_find_redirect(t_mini *mini, int i)
{
	t_cmd *cmd_node;
	t_token	*token_node;
	
	cmd_node = mini_redir_lstnew();
	token_node = mini->commands[i];
	while (token_node)
	{
		if (token_node->specie == OUT_REDIRECT)
			mini_handle_out_redir(cmd_node, token_node->next->token);
		else if (token_node->specie == IN_REDIRECT)
			mini_handle_in_redir(cmd_node, token_node->next->token);
		else if (token_node->specie == APPEND)
			mini_handle_append_redir(cmd_node, token_node->next->token);
		token_node = token_node->next;
	}
	mini_redir_lstadd_back(&mini->cmd_list, cmd_node);
}

void	mini_handle_out_redir(t_cmd *cmd_node, char *file)
{
	int fd;
	
	if (cmd_node->input_fd < 0 || cmd_node->output_fd < 0)
		return ;
	if (cmd_node->output_fd != 1)
		close(cmd_node->output_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 420);
	if (fd < 0)
		printf("open outfile error\n");
	cmd_node->output_fd = fd;
}

void	mini_handle_in_redir(t_cmd *cmd_node, char *file)
{
	int fd;

	if (cmd_node->input_fd < 0 || cmd_node->output_fd < 0)
		return ;
	if (cmd_node->input_fd != 0)
		close(cmd_node->input_fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		printf("open infile error\n");
	cmd_node->input_fd = fd;
}

void	mini_handle_append_redir(t_cmd *cmd_node, char *file)
{
	int fd;

	if (cmd_node->input_fd < 0 || cmd_node->output_fd < 0)
		return ;
	if (cmd_node->output_fd != 1)
		close(cmd_node->output_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 420);
	if (fd < 0)
		printf("open outfile append error\n");
	cmd_node->output_fd = fd;	
}
