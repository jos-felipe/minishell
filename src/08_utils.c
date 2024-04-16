/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:39:32 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/16 11:55:04 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define NAME 100
#define ERROR 200
#define VALUE 300

int	mini_env_identifier(char *str, t_dict **env_list, int start, int state)
{
	char	new_entry[2];
	int		i;

	new_entry[1] = NULL;
	i = -1;
	while (++i < ft_strlen(str) + 1)
	{
		state = mini_env_get_next_state(state, mini_env_get_column(str[i]));
		if (state == NAME)
		{
			new_entry[0] = mini_substr(str, start, i - start);
			start = i + 1;
		}
		if (state == VALUE)
			new_entry[1] = mini_substr(str, start, i - start);
		if (state == ERROR)
		{
			printf("export: not a valid identifier");
			return (1);
		}
	}
	ft_dictadd_back(env_list, ft_dictnew(new_entry));
	return (0);
}

int	mini_env_get_next_state(int state, int column)
{
	static int truth_table[3][4] =	{
										{200, 001, 200, 200},
										{200, 001, 002, 100},
										{002, 002, 002, 300}
									};
	return (truth_table[state][column]);
}

int	mini_env_get_column(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	if (c == '=')
		return (2);
	if (c == '\0')
		return (3);
	return (0);
}

char	*mini_substr(char *str, int start, int len)
{
	char	*substr;
	
	substr = ft_substr(str, start, len);
	ft_collect_mem(substr);
	return (str);
}
