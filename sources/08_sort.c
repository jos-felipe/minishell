/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:22 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/22 15:00:19 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_sort(t_list_push **a, t_list_push **b, int *rotations)
{
	int				rot_a;
	int				rot_b;
	unsigned int	bitshift;

	rot_a = rotations[0];
	rot_b = rotations[1];
	bitshift = sizeof(rot_a) * 8 - 1;
	if (push_lstsize(*b) > 1)
	{
		if (rot_a >> bitshift == rot_b >> bitshift)
			push_double_rotation(a, b, rotations);
		push_single_rot_b(b, &rotations[1]);
	}
	push_single_rot_a(a, &rotations[0]);
	push_gateway(PA, a, b);
}

void	push_double_rotation(t_list_push **a, t_list_push **b, int *rotations)
{
	int	i;

	i = -1;
	if (rotations[0] < 0)
		i = +1;
	while (rotations[0] != 0 && rotations[1] != 0)
	{
		if (i < 0)
			push_gateway(RR, a, b);
		else
			push_gateway(RRR, a, b);
		rotations[0] += i;
		rotations[1] += i;
	}
}

void	push_single_rot_a(t_list_push **a, int *rotation)
{
	int	i;

	i = -1;
	if (*rotation < 0)
		i = +1;
	while (*rotation != 0)
	{
		if (i < 0)
			push_gateway(RA, a, NULL);
		else
			push_gateway(RRA, a, NULL);
		*rotation += i;
	}
}

void	push_single_rot_b(t_list_push **b, int *rotation)
{
	int	i;

	i = -1;
	if (*rotation < 0)
		i = +1;
	while (*rotation != 0)
	{
		if (i < 0)
			push_gateway(RB, NULL, b);
		else
			push_gateway(RRB, NULL, b);
		*rotation += i;
	}
}
