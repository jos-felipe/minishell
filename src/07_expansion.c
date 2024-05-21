/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/21 16:00:35 by gfantoni         ###   ########.fr       */
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
	t_sub_token	*sub_token_lst;
	t_sub_token	*current;
	char	*sub_token;

	sub_token_lst = NULL;
	mini_sub_tokenizier(token, &sub_token_lst, 0, 0);
	current = sub_token_lst;
	while (current)
	{
		sub_token = current->content;
		if (sub_token[0] == '$' && sub_token[1])
			current->content = mini_search_and_replace(mini, sub_token);
		current = current->next;
	}
	return(mini_sub_token_join(sub_token_lst));
	
}

char	*mini_search_and_replace(t_mini *mini, char *sub_token)
{
	t_dict	*current;
	char	*new_sub_token;

	if (sub_token[1] == '?')
		return (mini_get_dollar_sign(mini, sub_token));
	if (mini_has_invalid_char(sub_token))
		return (mini_expand_with_invalid(mini, sub_token));
	current = mini->env_list;
	sub_token++;
	new_sub_token = NULL;
	while (current)
	{
		if (!ft_strncmp(current->key, sub_token, ft_strlen(sub_token)))
		{
			new_sub_token = current->value;
			break;
		}
		current = current->next;
	}
	return(new_sub_token);
}

char	*mini_expand_with_invalid(t_mini *mini, char *sub_token)
{
	char	*str_after_invalid;
	char	*str_before_invalid;
	
	if (mini_is_invalid_char(sub_token[1]))
		return (sub_token);
	str_after_invalid = mini_str_after_invalid_char(sub_token);
	str_before_invalid = mini_str_before_invalid_char(sub_token);
		
}

char	*mini_get_dollar_sign(t_mini *mini, char *sub_token)
{
	char	*status;
	char	*status_joined;
	
	status = ft_itoa(mini->status);
	ft_collect_mem(status);
	if (sub_token[2] != '\0')
	{
		sub_token++;
		sub_token++;
		status_joined = ft_strjoin(status, sub_token);
		ft_collect_mem(status_joined);
		return (status_joined);
	}
	return (status);
}
