/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:10:34 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/21 19:17:54 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_prompt(t_mini *mini)
{
	mini_ctrl_signal();
	mini->cmd_line = NULL;
	while (1)
	{
		mini->cmd_line = readline("prompt > ");
		if (mini->cmd_line == NULL)
		{
			printf("exit\n");
			mini_safe_exit(mini);
		}
		add_history(mini->cmd_line);
		mini_tokenizer(mini);
		// mini_execute(mini); TEMP COMMENT.
		mini_free_token_list(&mini->token_list);
		free(mini->cmd_line);
		// waitpid(mini->pid1, &mini->status, 0); TEMP COMMENT.
		mini->status = ft_get_exit_status(mini->status);
	}
}
