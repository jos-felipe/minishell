/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:16:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/09 12:04:05 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_3.h"

void	mini_init_env_list(t_mini *mini, char *envp[])
{
	int		i;
	char	**var;

	i = 0;
	while (environ[i])
	{
		var = ft_split(environ[i], ':');
		mini_env_lstadd_back(&mini->env_list, mini_env_lstnew(var));		
		i++;
	}
}

t_env	*mini_env_lstnew(char **var)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->key = var[0];
	new_node->value = var[1];
	new_node->next = NULL;
	collect_mem(var[0]);
	collect_mem(var[1]);
	collect_mem(var);
	collect_mem(new_node);
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
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

t_token	*mini_env_lstlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

char	*mini_sub_token_join(t_list *sub_token_lst)
{
	char	*sub_token;
	char	*str;

	str = NULL;
		while (sub_token_lst)
	{
		sub_token = sub_token_lst->content;
		if (!str)
			str = ft_strjoin(str, sub_token);
		else
			str = ft_strdup(sub_token);
		collect_mem(str);
		sub_token_lst = sub_token_lst->next;
	}
	return (str);
}