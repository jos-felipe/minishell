/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_dial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:08:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/22 15:03:11 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_dial(t_list_push **a)
{
	int	half;

	half = push_lstsize(*a) / 2;
	while ((*a)->index != 1)
	{
		if ((*a)->index > half)
			push_gateway(RA, a, NULL);
		else
			push_gateway(RRA, a, NULL);
	}
}
