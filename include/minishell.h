/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/14 13:19:59 by josfelip         ###   ########.fr       */
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

// 01_prompt.c
void	mini_init(t_pipex *mini);
void	mini_safe_exit(t_pipex *mini);
void	mini_prompt(t_pipex *mini);
int		main(int argc, char *argv[], char *envp[]);

// 02_ctrl_signal.c
void	mini_ctrl_signal(void);
void	sig_handler(int signum);

// 03_launch_executable.c
void	mini_execute(t_pipex *mini);

// 04_special_parameter.c
void	mini_special_parameter(t_pipex *mini);
char	*mini_expand(char c, t_pipex *mini);
int		ft_get_exit_status(int exit_status);

#endif