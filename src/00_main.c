/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/11 12:45:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	t_mini	mini;

	// mini_process_envp(&mini, envp);
	mini_ctrl_signal();
	mini_getenv(&mini);
	while (1)
	{
		mini_init(&mini);
		mini.cmd_line = readline("prompt > ");
		collect_mem(mini.cmd_line);
		if (mini.cmd_line == NULL)
			mini_ctrl_d_exit(&mini);
		add_history(mini.cmd_line);
		mini_tokenizer(&mini);
		if (!mini.syntax_error)
		{
			mini_parser(&mini);
			mini_expansion(&mini);
		}
		mini_free_trashman(get_mem_address());
		mini.status = ft_get_exit_status(mini.status);
	}
}
// mini_trashman(get_mem_address());
// mini_execute(mini); TEMP COMMENT.
// mini_free_token_list(&mini->token_list);
//free(mini->cmd_line);
// waitpid(mini->pid1, &mini->status, 0); TEMP COMMENT.
// 	mini_safe_exit(&mini);