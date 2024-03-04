/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_pre_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:55:22 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/22 14:56:49 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_all_save_three(t_list_push **a, t_list_push **b)
{
	int	stack_size;
	int	pushed;
	int	i;

	stack_size = push_lstsize(*a);
	pushed = 0;
	i = 0;
	while (stack_size > 6 && pushed <= stack_size / 2 && i < stack_size)
	{
		if ((*a)->index < stack_size / 2)
		{
			push_gateway(PB, a, b);
			pushed++;
		}
		else
			push_gateway(RA, a, NULL);
		i++;
	}
	i = 0;
	stack_size = stack_size - pushed;
	while (i < stack_size - 3)
	{
		push_gateway(PB, a, b);
		i++;
	}
}

void	push_tiny_sort(t_list_push **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->index;
	second = (*a)->next->index;
	third = (*a)->next->next->index;
	if (second > first && second > third)
		push_gateway(RRA, a, NULL);
	else if (first > second && first > third)
		push_gateway(RA, a, NULL);
	if (!push_is_sorted(*a))
		push_gateway(SA, a, NULL);
}

void	push_only_swap_or_tiny_sort(t_list_push **a, \
									t_list_push **b, \
									t_bst **bst)
{
	if (push_lstsize(*a) == 2)
	{
		push_gateway(SA, a, NULL);
		push_safe_exit(0, a, b, bst);
	}
	else if (push_lstsize(*a) == 3)
	{
		push_tiny_sort(a);
		push_safe_exit(0, a, b, bst);
	}
}
