/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:16:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/11 16:35:42 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_getenv(t_mini *mini)
{
	int		i;
	int		start;
	int		len;
	char	*var[2];

	i = 0;
	while (__environ[i])
	{
		start = 0;
		len = mini_strchr_index(__environ[i], '=');
		if (len > -1)
		{
			var[0] = ft_substr(__environ[i], start, len);
			ft_collect_mem(var[0]);
			start = len + 1;
			len = ft_strlen(__environ[i]) - start;
			var[1] = ft_substr(__environ[i], start, len);
			ft_collect_mem(var[1]);
			ft_dictadd_back(&mini->env_list, ft_dictnew(var));
		}
		i++;
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
			ft_collect_mem(str);
		}
		sub_token_lst = sub_token_lst->next;
	}
	return (str);
}