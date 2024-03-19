/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_launch_executable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:11:53 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/19 15:25:14 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_parse_readline(t_pipex *mini)
{
	mini->pathname = NULL;
	if (mini->cmd_line)
	{
		if (mini->cmd_line[0] == '\0')
			return ;
		mini->split_cmd_line = ft_split(mini->cmd_line, ' ');
		if (mini->split_cmd_line == NULL)
		{
			mini->status = EXIT_FAILURE;
			ft_printf("Memory allocation failed for command line.\n");
			mini_free_split(mini->split_cmd_line);
			mini_safe_exit(mini);
		}
		mini_analysis(mini);
		// mini->pathname = mini_whereis(mini->split_cmd_line[0], mini->path); TEMP COMMENT.
		// if (mini->pathname == NULL)
		// 	ft_printf("Command not found: %s\n", mini->split_cmd_line[0]);
		// else
		// 	ft_lstadd_back(&mini->lst_memory, ft_lstnew(mini->pathname));
		mini_special_parameter(mini);
	}
}
void	mini_process_envp(t_pipex *mini, char *envp[])
{
	mini->path = mini_get_path(envp);
	if (mini->path == NULL)
	{
		ft_printf("PATH not found\n");
		mini->status = EXIT_FAILURE;
		mini_safe_exit(mini);
	}
	mini_trashman_collector(&mini->lst_memory, mini->path);
	if (mini->lst_memory == NULL)
	{
		ft_printf("Memory allocation failed: new list.\n");
		mini->status = EXIT_FAILURE;
		mini_safe_exit(mini);
	}
}

void	mini_execute(t_pipex *mini)
{
	if (!mini->pathname)
		return ;
	mini->pid1 = fork();
	if (mini->pid1 < 0)
		mini_safe_exit(mini);
	if (mini->pid1 == 0)
		execve(mini->pathname, mini->split_cmd_line, NULL);
}
