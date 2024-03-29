/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:29:13 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/29 17:53:57 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_parser(t_mini *mini)
{
	int		nbr_cmds;

	nbr_cmds = 0;
	if (mini->token_list)
	{
		nbr_cmds = mini_count_nbr_pipes(mini->token_list) + 1;
		mini->commands = (t_token **)malloc(sizeof(t_token *) * nbr_cmds + 1);
		collect_mem(mini->commands);
		mini_fill_cmd_array(mini);
		debug_print_array_list(mini); // FOR DEBUG ONLY
	}
}

int	mini_count_nbr_pipes(t_token *token_list)
{
	t_token *temp;
	int		nbr_pipes;

	temp = token_list;
	nbr_pipes = 0;
	while (temp)
	{
		if (temp->token[0] == '|')
			nbr_pipes++;
		temp = temp->next;
	}
	return (nbr_pipes);
}

void	mini_fill_cmd_array(t_mini  *mini)
{
	t_token *temp;
	int		i;

	i = 0;
	mini->commands[i++] = mini->token_list;
	while (mini->token_list)
	{
		temp = mini->token_list;
		if (temp->token[0] == '|')
		{
			mini->commands[i++] = temp->next;
			mini->token_list = mini->token_list->next;
			temp->prev->next = NULL;
		}
		else
			mini->token_list = mini->token_list->next;
	}
}