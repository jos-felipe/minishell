/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/11 16:06:49 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int main(void)
{
	t_mini	mini;

	mini_ctrl_signal(&mini);
	mini_getenv(&mini);
	mini.status = 0;
	while (42)
	{
		mini.int_action.sa_handler = sig_handler;
		sigaction(SIGINT, &mini.int_action, NULL);
		mini.quit_action.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &mini.quit_action, NULL);
		mini_init(&mini);
		mini.cmd_line = readline("prompt > ");
		ft_collect_mem(mini.cmd_line);
		if (mini.cmd_line == NULL)
		{
			mini_ctrl_d_exit();
			break;
		}
		if (mini.cmd_line[0] == '\0')
			continue;
		add_history(mini.cmd_line);
		mini_tokenizer(&mini);
		if (!mini.syntax_error && mini.token_list)
		{
			mini_parser(&mini);
			// printf("token 0: %s token 1: %s\n", mini.token_list->token, mini.token_list->next->token);
			// printf("token 0: %s token 1: %s\n", mini.commands[0]->token, mini.commands[0]->next->token);
			mini_expansion(&mini);
			// printf("token 0: %s token 1: %s\n", mini.commands[0]->token, mini.commands[0]->next->token);
			mini_redirect(&mini);
			mini_execute(&mini);
		}
		// ft_free_trashman(ft_get_mem_address());
	}
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
}
