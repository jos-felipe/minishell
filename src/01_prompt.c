/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:10:34 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 10:04:04 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/pipex.h"

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
		mini->split_cmd_line = NULL;
		mini_parse_readline(mini);
		// mini_execute(mini); TEMP COMMENT.
		mini_free_split(mini->split_cmd_line);
		free(mini->cmd_line);
		// waitpid(mini->pid1, &mini->status, 0); TEMP COMMENT.
		mini->status = ft_get_exit_status(mini->status);
	}
}
