/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:06:28 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/23 18:24:45 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_swap(t_list_push **a, t_list_push **b, int *rotations)
{
	while (*b)
	{
		push_target_pos(*a, *b);
		push_comp_cost(*a, *b);
		push_cheapest_move(*b, rotations);
		push_sort(a, b, rotations);
	}
	push_dial(a);
}
