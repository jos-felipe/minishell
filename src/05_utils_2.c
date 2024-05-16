/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:38:07 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/16 19:26:05 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_print_sintax_error_message(int state)
{
	if (state == 200)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unterminated quoted string\n");
	else if (state == 201)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
	else if (state == 202)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error: not a bonus project '||'\n");
}

void	mini_cut_string(t_mini *mini, t_dfa *dfa)
{
	dfa->value = ft_substr(mini->cmd_line, dfa->start, (dfa->i - dfa->start) + 1 - dfa->quote);
	ft_collect_mem(dfa->value);
	mini_token_lstadd_back(&mini->token_list, mini_token_lstnew(dfa->value, dfa->state));
	dfa->state = 0;
	dfa->quote = 0;
}

void	mini_check_pipe_sintax(t_mini *mini, t_token *token_list)
{
	if (token_list->token[0] == '|')
	{
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");	
		mini->syntax_error = 1;
		return;
	}
	while (token_list)
	{
		if (token_list->token[0] == '|' && token_list->next == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
			mini->syntax_error = 1;
			return;
		}
		token_list = token_list->next;
	}
}

void	mini_check_consecutive_op_sintax(t_mini *mini, t_token *token_list)
{
	while (token_list)
	{
		if (token_list->gender == OPERATOR && token_list->specie != PIPE)
		{
			if (token_list->next && token_list->next->gender == OPERATOR)
			{
				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
				mini->syntax_error = 1;
				return;
			}
		}
		token_list = token_list->next;
	}
}
