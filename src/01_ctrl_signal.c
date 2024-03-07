/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_ctrl_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/07 20:11:55 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_ctrl_signal(void)
{
	struct	sigaction int_action;
	struct	sigaction old_int_action;
	struct	sigaction quit_action;

    int_action.sa_handler = sig_handler;
    sigemptyset(&int_action.sa_mask);
    int_action.sa_flags = 0;
	sigaction(SIGINT, NULL, &old_int_action);
	if (old_int_action.sa_handler != SIG_IGN)
		sigaction(SIGINT, &int_action, NULL);
    quit_action.sa_handler = SIG_IGN;
    sigemptyset(&quit_action.sa_mask);
	sigaction(SIGQUIT, &quit_action, NULL);
}

void	sig_handler(int signum) 
{
	if (signum == SIGINT)
		printf("\nprompt > ");
}