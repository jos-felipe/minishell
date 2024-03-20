/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_analysis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:44 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/20 17:38:04 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_analysis(t_pipex *mini)
{
	automaton(mini->cmd_line, &mini->token_list, 0, 0);

}

void	automaton(char *str, t_token **token_list, int start, int state)
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
		state = get_next_state(state, get_column(str[i]));
		if (is_end_state(state) && state != NULL_CHAR)
		{
			if (is_back_state(state))
				i--;
			if (is_weird_state(state))
			{
				state = WORD;
				i -= 2;
			}
			value = ft_substr(str, start, (i - start) + 1);
			ft_lstadd_back_token(token_list, ft_lstnew_token(value, state));
			state = 0;
		}
		i++;
	}
}

int	get_next_state(int state, int column)
{
	static int true_table[6][8] = {
									{1, 2,   3,   4,   5,   105, 0,   666},
									{1, 100, 100, 100, 100, 100, 100, 100},
									{101, 101, 201, 201, 201, 201, 201, 201, 201, 201, 201},
									{103, 203, 102, 203, 203, 203, 203, 203, 203, 203, 203},
									{4, 202, 202, 8, 202, 202, 202, 202, 202, 7, 5},
									{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4},
								  };
	return (true_table[state][column]);
}


