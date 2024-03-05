/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/05 17:08:43 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../lib/includes/libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// 00_prompt.c
void	mini_safe_exit(int status, char *line);
void	mini_prompt(void);
int		main(void);


// 01_ctrl_signal.c
void	mini_ctrl_signal(void);
void	mini_signal_installer(int signum, struct sigaction *act);
void	sig_handler(int signum);

#endif