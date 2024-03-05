/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_ctrl_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/05 17:50:20 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_ctrl_signal(void)
{
	struct	sigaction sa;
	struct	sigaction sa_quit;

    sa.sa_handler = sig_handler;
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sigemptyset(&sa_quit.sa_mask);
    sa.sa_flags = 0;
	mini_signal_installer(SIGINT, &sa);
	mini_signal_installer(SIGQUIT, &sa_quit);
	
}

void	mini_signal_installer(int signum, struct sigaction *act)
{
	if (sigaction(signum, act, NULL) == -1) 
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	sig_handler(int signum) 
{
	if (signum == SIGINT)
		printf("\nprompt > ");
}