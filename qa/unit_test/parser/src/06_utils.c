/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:29:20 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/30 14:50:59 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	debug_print_array_list(t_mini *mini) // FOR DEBUG ONLY
{
	int i;

	i = 0;
	while (mini->commands[i])
	{
		debug_print_parse_list(&mini->commands[i]);
		printf("\n");	
		i++;
	}
}

void	debug_print_parse_list(t_token **head) // FOR DEBUG ONLY
{
	t_token *node;

	node = *head;
	while (node)
	{
		printf("%s ", (char *)node->token);
		node = node->next;
	}
}