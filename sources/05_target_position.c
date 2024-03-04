/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_target_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:04:50 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/22 15:25:06 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_target_pos(t_list_push *a, t_list_push *b)
{
	int	b_index;

	push_get_positon(a);
	push_get_positon(b);
	while (b)
	{
		b_index = b->index;
		b->target_pos = push_target_comp(b_index, a);
		b = b->next;
	}
}

int	push_target_comp(int b_index, t_list_push *a)
{
	int			a_index;
	int			a_min;
	int			pos;
	t_list_push	*temp;

	a_min = INT_MAX;
	temp = a;
	while (a)
	{
		a_index = a->index;
		if (a_index > b_index && a_index <= a_min)
		{
			a_min = a_index;
			pos = a->position;
		}
		a = a->next;
	}
	a = temp;
	if (a_min == INT_MAX)
		pos = push_target_min(a);
	return (pos);
}

int	push_target_min(t_list_push *a)
{
	int	a_min;
	int	a_index;
	int	pos;

	a_min = INT_MAX;
	while (a)
	{
		a_index = a->index;
		if (a_index <= a_min)
		{
			a_min = a_index;
			pos = a->position;
		}
		a = a->next;
	}
	return (pos);
}

void	push_get_positon(t_list_push *node)
{
	int	i;

	i = 0;
	while (node)
	{
		node->position = i;
		i++;
		node = node->next;
	}
}
