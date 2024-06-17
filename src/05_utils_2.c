/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:38:07 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 14:48:42 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_print_sintax_error_message(int state)
{
	if (state == 200)
		ft_printf_fd(STDERR_FILENO, \
		"minishell: syntax error: unterminated quoted string\n");
	else if (state == 201)
		ft_printf_fd(STDERR_FILENO, \
		"minishell: syntax error near unexpected token\n");
	else if (state == 202)
		ft_printf_fd(STDERR_FILENO, \
		"minishell: syntax error: not a bonus project '||'\n");
}

void	mini_cut_string(t_mini *mini, t_dfa *dfa)
{
	dfa->value = ft_substr(mini->cmd_line, dfa->start, \
	(dfa->i - dfa->start) + 1 - dfa->quote);
	ft_collect_mem(dfa->value);
	mini_token_lstadd_back(&mini->token_list, \
	mini_token_lstnew(dfa->value, dfa->state));
	dfa->state = 0;
	dfa->quote = 0;
}

static int	mini_pipe_syntax(t_token *token_node)
{
	if (token_node->token[0] == '|' && token_node->next == NULL)
		return (1);
	return (0);
}

static int	mini_consecutive_op_syntax(t_token *token_node)
{
	if (token_node->gender == OPERATOR && token_node->specie != PIPE)
		if (token_node->next && token_node->next->gender == OPERATOR)
			return (1);
	return (0);
}

static int	mini_pipe_space_pipe_syntax(t_token *token_node)
{
	if (token_node->next)
		if (token_node->token[0] == '|' && token_node->next->token[0] == '|')
			return (1);
	return (0);
}
