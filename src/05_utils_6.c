/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:38:07 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 14:48:20 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return ;
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
				return ;
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