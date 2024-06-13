/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:38:07 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/13 16:03:03 by gfantoni         ###   ########.fr       */
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

static int mini_pipe_syntax(t_token *token_node)
{
	if (token_node->token[0] == '|' && token_node->next == NULL)
		return (1);
	return (0);
}

static int mini_consecutive_op_syntax(t_token *token_node)
{
	if (token_node->gender == OPERATOR && token_node->specie != PIPE)
		if (token_node->next && token_node->next->gender == OPERATOR)
			return (1);
	return (0);
}

static int mini_pipe_space_pipe_syntax(t_token *token_node)
{
	if (token_node->next)
		if (token_node->token[0] == '|' && token_node->next->token[0] == '|')
			return (1);
	return (0);
}

static void	mini_set_syntax_error(t_mini *mini)
{
	ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");	
	mini->syntax_error = 1;
	mini->status = 2; 
}

void	mini_check_sintax(t_mini *mini, t_token *token_list)
{
	int		stdin_backup;
	int		stdout_backup;
	
	if (token_list && token_list->token[0] == '|')
	{
		mini_set_syntax_error(mini);
		return;
	}
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	mini->int_action.sa_handler = sig_handler_heredoc;
	sigaction(SIGINT, &mini->int_action, NULL);
	while (token_list)
	{
		if (token_list->specie == HERE_DOC)
		{
			if (mini_is_valid_heredoc(token_list->next))
				mini_handle_heredoc(mini, token_list->next);
			else
			{
				mini_set_syntax_error(mini);
				return;		
			}
		}
		if (mini_pipe_syntax(token_list) || mini_consecutive_op_syntax(token_list) || 
			mini_pipe_space_pipe_syntax(token_list))
		{
			mini_set_syntax_error(mini);
			return;
		}
		token_list = token_list->next;
	}
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}


// void	mini_check_consecutive_op_sintax(t_mini *mini, t_token *token_list)
// {
// 	while (token_list)
// 	{
// 		if (token_list->gender == OPERATOR && token_list->specie != PIPE)
// 		{
// 			if (token_list->next && token_list->next->gender == OPERATOR)
// 			{
// 				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
// 				mini->syntax_error = 1;
// 				mini->status = 2; 
// 				return;
// 			}
// 		}
// 		token_list = token_list->next;
// 	}
// }


// void	mini_check_pipe_space_pipe_sintax(t_mini *mini, t_token *token_list)
// {
// 	while (token_list->next)
// 	{
// 		if (token_list->token[0] == '|' && token_list->next->token[0] == '|')
// 		{
// 			ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
// 			mini->syntax_error = 1;
// 			mini->status = 2; 
// 			return;
// 		}
// 		token_list = token_list->next;
// 	}
// }