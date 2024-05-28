/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:23:01 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/28 14:24:27 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_is_valid_heredoc(t_token *token_node)
{
	if (token_node && token_node->gender == WORD)
		return (1);
	return (0);
}

void	mini_handle_heredoc(t_mini *mini, t_token *token_node)
{
	
}