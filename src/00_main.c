/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/02 12:21:48 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	argc = 0;
	argv = NULL;
	mini_process_envp(&mini, envp);
	mini_ctrl_signal();
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
			mini_parser(&mini);
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