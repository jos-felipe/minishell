/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:16:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:28 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_init_env_list(t_mini *mini)
{
	int		i;
	char	*env_line;
	int		split_index;
	char	*var[2];

	i = 0;
	env_line = __environ[i];
	while (env_line)
	{
		split_index = mini_strchr_index(env_line, '=');
		if (split_index != -1)
		{
			var[0] = mini_substr_index(env_line, 0, split_index - 1);
			var[1] = mini_substr_index(env_line, split_index + 1, ft_strlen(env_line));
			mini_env_lstadd_back(&mini->env_list, mini_env_lstnew(var));
		}
		i++;
		env_line = __environ[i];
	}
}

int	mini_strchr_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*mini_substr_index(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*substr;

	i = start;
	j = 0;
	substr = (char *)calloc(end - start + 2, sizeof(char));
	collect_mem(substr);
	while (i <= end)
	{
		substr[j] = str[i]; 
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}


t_env	*mini_env_lstnew(char **var)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	collect_mem(new_node);
	if (new_node == NULL)
		return (NULL);
	new_node->key = var[0];
	new_node->value = var[1];
	new_node->next = NULL;
	return (new_node);
}

void	mini_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_env_lstlast(*lst);
	last_node->next = new;
}

t_env	*mini_env_lstlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

char	*mini_sub_token_join(t_sub_token *sub_token_lst)
{
	char	*sub_token;
	char	*str;

	str = NULL;
	while (sub_token_lst)
	{
		sub_token = sub_token_lst->content;
		if (sub_token)
		{
			if (str)
				str = ft_strjoin(str, sub_token);
			else
				str = ft_strdup(sub_token);
			collect_mem(str);
		}
		sub_token_lst = sub_token_lst->next;
	}
	return (str);
}