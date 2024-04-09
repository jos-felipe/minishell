/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:39:32 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/09 12:34:17 by gfantoni         ###   ########.fr       */
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
		if (state >= 100 && state != NULL_CHAR)
		{
			if (is_one_back_state(state))
				i = i - 1;
			else if (is_two_back_state(state))
				i = i - 2;
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
	static int truth_table[4][3] = {
									{1,   3,   666},
									{1,   2,   100},
									{200, 200, 100},
									{1,   300, 100}
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

int is_one_back_state(int state)
{
	if (state == 100)
		return (1);
	return (0);
}

int is_two_back_state(int state)
{
	if (state == 200)
		return (1);
	return (0);
}