/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_analysis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:44 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/21 12:03:38 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"
#define NULL_CHAR 106

void	mini_analysis(t_mini *mini)
{
	automaton(mini->cmd_line, &mini->token_list, 0, 0);
	debug_print_list(&mini->token_list);

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
			if (is_error_state(state))
			{
				
				break;
			}
			value = ft_substr(str, start, (i - start) + 1);
			mini_lstadd_back(token_list, mini_lstnew(value));
			state = 0;
		}
		i++;
	}
}

int	get_next_state(int state, int column)
{
	static int truth_table[6][8] = {
									{1,   2,   3,   4,   5,   105, 0,   666},
									{1,   100, 100, 100, 100, 100, 100, 100},
									{101, 102, 101, 101, 101, 101, 101, 101},
									{103, 103, 104, 103, 103, 103, 103, 103},
									{4,   4,   4,   107, 4,   4,   4,   106},
									{5,   5,   5,   5,   108, 5,   5,   106},
								  };
	return (truth_table[state][column]);
}

int	get_column(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (2);
	if (c == '\"')
		return (3);
	if (c == '\'')
		return (4);
	if (c == '|')
		return (5);
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (6);
	if (c == '\0')
		return (7);
	return (0); // word
}

int	is_end_state(int num)
{
	if (num >= 100)
		return (1);
	return (0);
}

int	is_back_state(int num)
{
	if (num == 100 || num == 101 || num == 103)
		return (1);
	return (0);
}
int	is_error_state(int num)
{
	if (num == 106)
		return (1);
	return (0);
}

