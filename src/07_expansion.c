/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/08 09:58:21 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_expansion(t_mini *mini)
{
	int		i;
	t_token	*cmd;

	i = 0;
	cmd = mini->commands[i];
	while (cmd)
	{
		mini_token_expansion(cmd, mini);
		i++;
		cmd = mini->commands[i];
	}
}

void	mini_token_expansion(t_mini *mini, int i)
{
	t_token	*cmd;
	
	cmd = mini->commands[i];
	while (cmd)
	{
		if (is_dollar_sign(cmd->token))
			mini_search_and_replace(mini, i);
		cmd = cmd->next;
	}
}

void	mini_search_and_replace(t_mini *mini, int i)
{
	char	*old_token;
	char	*new_token;
	t_env	*current;

	old_token = mini->commands[i]->token;
	old_token++;
	current = mini->env_list;
	new_token = NULL;
	while (current)
	{
		if (current->key == old_token)
		{
			new_token = current->content;
			break;
		}
		current = current->next;
	}
	mini->commands[i]->token = new_token;
}
