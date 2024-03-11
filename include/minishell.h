/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/11 13:27:58 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "../include/pipex.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// 00_prompt.c
void	mini_init(t_pipex *mini);
void	mini_safe_exit(t_pipex *mini);
void	mini_prompt(t_pipex *mini);
int		main(int argc, char *argv[], char *envp[]);

// 01_ctrl_signal.c
void	mini_ctrl_signal(void);
void	sig_handler(int signum);

#endif