/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:16:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/08 17:40:05 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_init_env_list(t_mini *mini, char *envp[])
{

	
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