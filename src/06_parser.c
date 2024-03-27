/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:29:13 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/27 15:03:29 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_parser(t_mini *mini)
{
	char 	*commands;
	int		nbr_cmds;

	nbr_cmds = 0;
	if (mini->token_list)
	{
		nbr_cmds = mini_count_nbr_pipes(mini->token_list) + 1;
		commands = malloc(sizeof(t_token *) * nbr_cmds + 1);
		//mini_fill_cmd_array(mini, commands);
	}
	printf("%d\n", nbr_cmds);
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

// void	mini_fill_cmd_array(t_mini  *mini, char *commands)
// {
// 	t_token *temp;

// 	temp = mini->
	
// }