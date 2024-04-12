/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:44 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/12 11:56:12 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_tokenizer(t_mini *mini)
{
	mini->pathname = NULL;
	if (mini->cmd_line)
	{
		if (mini->cmd_line[0] == '\0')
			return ;
		mini->syntax_error = mini_automaton(mini->cmd_line, &mini->token_list, 0, 0);
		if (!mini->syntax_error)
			mini->syntax_error = mini_check_pipe_sintax(mini->token_list);
		if (!mini->syntax_error)
			mini->syntax_error = mini_check_consecutive_op_sintax(mini->token_list);
		// debug_print_list(&mini->token_list);
		// mini->pathname = mini_whereis(mini->split_cmd_line[0], mini->path); TEMP COMMENT.
		// if (mini->pathname == NULL)
		// 	ft_printf("Command not found: %s\n", mini->split_cmd_line[0]);
		// else
		// 	ft_lstadd_back(&mini->lst_memory, ft_lstnew(mini->pathname));
		// mini_special_parameter(mini);
	}
}

int	mini_automaton(char *str, t_token **token_list, int start, int state)
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
			if (mini_is_back_state(state))
				i--;
			if (mini_is_error_state(state))
			{
				mini_print_sintax_error_message(state);
				return (1);
			}
			value = ft_substr(str, start, (i - start) + 1);
			ft_collect_mem(value);
			mini_token_lstadd_back(token_list, mini_token_lstnew(value, state));
			state = 0;
		}
		i++;
	}
	return (0);
}

int	mini_get_next_state(int state, int column)
{
	static int truth_table[7][8] = {
									{1,   2,   3,   4,   5,   6,   0,   666},
									{1,   100, 100, 100, 100, 100, 100, 100},
									{101, 102, 101, 101, 101, 101, 101, 101},
									{103, 103, 104, 103, 103, 103, 103, 103},
									{4,   4,   4,   107, 4,   4,   4,   200},
									{5,   5,   5,   5,   108, 5,   5,   200},
									{105, 105, 105, 105, 105, 1, 105,   201},
								  };
	return (truth_table[state][column]);
}

int	mini_get_column(char c)
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

