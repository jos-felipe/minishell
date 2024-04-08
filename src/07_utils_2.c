/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:39:32 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/08 18:53:33 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define NULL_CHAR 666

void	mini_sub_tokenizier(char *str, t_list **sub_token_lst, int start, int state)
{
	int		i;
	char	*value;
	int		size;

	i = 0;
	size = ft_strlen(str) + 1;
	while (i < size)
	{
		if (state == 0)
			start = i;
		state = mini_get_next_state(state, mini_get_column(str[i]));
		if (mini_is_end_state(state) && state != NULL_CHAR)
		{
			i--;
			value = ft_substr(str, start, (i - start) + 1);
			collect_mem(value);
			ft_lstadd_back(sub_token_lst, ft_lstnew(value));
			state = 0;
		}
		i++;
	}
	
}

int	mini_get_next_state(int state, int column)
{
	static int truth_table[3][3] = {
									{1,   2,   666},
									{1,   100, 100},
									{2,   101, 102}
								  };
	return (truth_table[state][column]);
}

int	mini_get_column(char c)
{
	if (c == '$')
		return (1);
	if (c == '\0')
		return (2);
	return (0); // word
}