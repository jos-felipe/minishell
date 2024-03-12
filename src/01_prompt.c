/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:10:34 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/12 16:22:52 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/pipex.h"

void	mini_prompt(t_pipex *mini)
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
		mini_execute(mini);
		mini_free_split(mini->split_cmd_line);
		free(mini->cmd_line);
		waitpid(mini->pid1, NULL, 0);
	}
}