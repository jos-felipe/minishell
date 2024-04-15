/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:47 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/15 16:57:29 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_is_end_state(int num)
{
	if (num >= 100)
		return (1);
	return (0);
}

int	mini_is_back_state(int num)
{
	if (num == 100 || num == 101 || num == 103 || num == 105)
		return (1);
	return (0);
}
int	mini_is_error_state(int num)
{
	if (num >= 200)
		return (1);
	return (0);
}

int	mini_is_quote_state(int num)
{
	if (num == 107 || num == 108)
		return (1);
	return (0);
}

void	mini_print_sintax_error_message(int state)
{
	if (state == 200)
		ft_printf("error: quote was not closed properly\n");
	else if (state == 201)
		ft_printf("bash: syntax error near unexpected token `|'\n");
	else if (state == 202)
		ft_printf("error: not a bonus project '||'\n");
}
