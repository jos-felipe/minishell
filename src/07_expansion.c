/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/21 19:41:48 by gfantoni         ###   ########.fr       */
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

int		mini_has_invalid_char(char *sub_token)
{
	int i;
	
	sub_token++;
	i = 0;
	while (sub_token[i])
	{
		if (sub_token[i] < 48 || 
			(sub_token[i] > 57 && sub_token[i] < 65) || 
			(sub_token[i] > 90 && sub_token[i] < 97) || 
			sub_token[i] > 122)
			return (1);
		i++;
	}
	return (0);
}

char	*mini_expand_with_invalid(t_mini *mini, char *sub_token)
{
	char	*str_joined;
	char	*str_expanded;
	char	*str_after_invalid;
	char	*str_before_invalid;
	
	if (mini_is_invalid_char(sub_token[1]))
		return (sub_token);
	str_after_invalid = mini_str_after_invalid_char(sub_token);
	str_before_invalid = mini_str_before_invalid_char(sub_token);
	str_expanded = mini_search_and_replace(mini, str_before_invalid);
	str_joined = ft_strjoin_expansion(str_expanded, str_after_invalid);
	ft_collect_mem(str_joined);
	return (str_joined);
}

int		mini_is_invalid_char(char c)
{
	if (c < 48 || 
		(c > 57 && c < 65) || 
		(c > 90 && c < 97) || 
		c > 122)
		return (1);
	return (0);
}

char	*mini_str_after_invalid_char(char *sub_token)
{
	char	*str_after;
	int i;
	
	str_after = ft_calloc(sizeof(char), ft_strlen(sub_token) + 1);
	ft_collect_mem(str_after);
	sub_token++;
	i = 0;
	while (*sub_token)
	{
		if (*sub_token < 48 || 
			(*sub_token > 57 && *sub_token < 65) || 
			(*sub_token > 90 && *sub_token < 97) || 
			*sub_token > 122)
			break;
		sub_token++;
	}
	i = 0;
	while (sub_token[i])
	{
		str_after[i] = sub_token[i];
		i++;
	}
	return (str_after);
}

char	*mini_str_before_invalid_char(char *sub_token)
{
	char	*str_before;
	int 	i;
	
	str_before = ft_calloc(sizeof(char), ft_strlen(sub_token) + 1);
	ft_collect_mem(str_before);
	sub_token++;
	i = 0;
	while (sub_token[i])
	{
		if (sub_token[i] < 48 || 
			(sub_token[i] > 57 && sub_token[i] < 65) || 
			(sub_token[i] > 90 && sub_token[i] < 97) || 
			sub_token[i] > 122)
			break;
		str_before[i] = sub_token[i];
		i++;
	}
	return (str_before);
}

char	*ft_strjoin_expansion(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	c;
	size_t	z;

	if (!s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	c = 0;
	if (s1)
	{
		while (s1[c] != '\0')
		{
			new[c] = s1[c];
			c++;
		}
	}
	z = 0;
	while (s2[z] != '\0')
		new[c++] = s2[z++];
	new[c] = '\0';
	return (new);
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
