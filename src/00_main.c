/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/08 15:34:35 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	t_mini	mini;

	mini_ctrl_signal();
	mini_getenv(&mini);
	while (42)
	{
		mini_init(&mini);
		mini.cmd_line = readline("prompt > ");
		ft_collect_mem(mini.cmd_line);
		if (mini.cmd_line == NULL)
			mini_ctrl_d_exit(&mini);
		add_history(mini.cmd_line);
		mini_tokenizer(&mini);
		if (!mini.syntax_error)
		{
			mini_parser(&mini);
			mini_expansion(&mini);
			mini_redirect(&mini);
			mini_execute(&mini);
		}
		ft_free_trashman(ft_get_mem_address());
		mini.status = ft_get_exit_status(mini.status);
	}
}
