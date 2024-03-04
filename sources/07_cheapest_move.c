/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_cheapest_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:05:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/26 09:27:34 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_cheapest_move(t_list_push *b, int *rotations)
{
	int			total_cost;

	total_cost = INT_MAX;
	while (b)
	{
		if (push_abs(b->cost_a) + push_abs(b->cost_b) < total_cost)
		{
			rotations[0] = b->cost_a;
			rotations[1] = b->cost_b;
			total_cost = push_abs(b->cost_a) + push_abs(b->cost_b);
		}
		b = b->next;
	}
}
