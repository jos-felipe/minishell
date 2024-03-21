/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 12:58:28 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	argc = 0;
	argv = NULL;
	mini_init(&mini);
	mini_process_envp(&mini, envp);
	mini_prompt(&mini);
	mini_safe_exit(&mini);
}