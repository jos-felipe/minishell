/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:10:40 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 13:05:17 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/pipex.h"

t_analysis	*init_analysis(void)
{
	t_analysis	*analysis;

	analysis = (t_analysis *)malloc(sizeof(t_analysis));
	analysis->command = NULL;
	analysis->arguments = NULL;
	analysis->input_fd = -1;
	analysis->output_fd = -1;
	analysis->append = -1;
	return (analysis);
}

void	mini_init(t_pipex *pipex)
{
	pipex->infile = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->outfile = NULL;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->fd_pipe[0] = -1;
	pipex->fd_pipe[1] = -1;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
	pipex->path = NULL;
	pipex->argv1 = NULL;
	pipex->argv2 = NULL;
	pipex->fn1 = NULL;
	pipex->fn2 = NULL;
	pipex->lst_memory = NULL;
	pipex->status = 0;
	pipex->cmd_line = NULL;
	pipex->split_cmd_line = NULL;
	pipex->pathname = NULL;
	pipex->analysis = init_analysis();
}
void	mini_safe_exit(t_pipex *mini)
{
	clear_history();
	mini_trashman(mini->lst_memory);
	exit(mini->status);
}