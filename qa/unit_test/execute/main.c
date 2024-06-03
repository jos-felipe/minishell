/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/03 16:13:21 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	mini_init(&mini);
	mini_getenv(&mini);
	mini.cmd_line = argv[1];
	mini_tokenizer(&mini);
	mini_parser(&mini);
	mini_expansion(&mini);
	mini_redirect(&mini);
	mini_execute(&mini);
	
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	return (0);
}