/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/08 17:35:51 by josfelip         ###   ########.fr       */
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
		mini_token_expansion(mini, i);
		i++;
		cmd = mini->commands[i];
	}
}

void	mini_token_expansion(t_mini *mini, int i)
{
	t_token	*token_node;
	
	token_node = mini->commands[i];
	while (token_node)
	{
		if (ft_strchr(token_node->token, '$'))
			token_node->token = mini_sep_exp_join(mini, token_node->token);
		token_node = token_node->next;
	}
}

char	*mini_sep_exp_join(t_mini *mini, char *token)
{
	t_list	*sub_token_lst;
	char	*sub_token;

	sub_token_lst = NULL;
	mini_sub_tokenizier(&sub_token_lst, token);
	while (sub_token_lst)
	{
		sub_token = sub_token_lst->sub_token;
		if (sub_token[0] == '$' && sub_token[1])
			sub_token_lst->sub_token = mini_search_and_replace(mini, sub_token);
		sub_token_lst = sub_token_lst->next;
	}
	return(mini_sub_token_join(sub_token_lst));
	
}

char	*mini_search_and_replace(t_mini *mini, char *sub_token)
{
	t_env	*current;
	char	*new_sub_token;

	current = mini->env_list;
	sub_token++;
	new_sub_token = NULL;
	while (current)
	{
		if (!ft_strncmp(current->key, sub_token, ft_strlen(sub_token)))
		{
			new_sub_token = current->content;
			break;
		}
		current = current->next;
	}
	return(new_sub_token);
}
