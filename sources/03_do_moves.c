/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_do_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:55:17 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/22 14:58:13 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_do_sx(t_list_push **stack, char *sx)
{
	t_list_push	*node_1;
	t_list_push	*node_2;
	t_list_push	*node_3;

	node_1 = (*stack)->next;
	node_2 = *stack;
	node_3 = (*stack)->next->next;
	*stack = node_1;
	(*stack)->next = node_2;
	(*stack)->next->next = node_3;
	if (sx != NULL)
		ft_printf("%s\n", sx);
}

void	push_do_rrx(t_list_push **stack, char *rrx)
{
	t_list_push	*node_1;
	t_list_push	*node_2;
	t_list_push	*node_n;

	node_1 = push_lstlast(*stack);
	node_2 = *stack;
	node_n = push_lst_n_1(*stack);
	*stack = node_1;
	(*stack)->next = node_2;
	node_n->next = NULL;
	if (rrx != NULL)
		ft_printf("%s\n", rrx);
}

void	push_do_rx(t_list_push **stack, char *rx)
{
	t_list_push	*node_1;
	t_list_push	*node_n_1;
	t_list_push	*node_n;

	node_1 = (*stack)->next;
	node_n_1 = push_lstlast(*stack);
	node_n = *stack;
	*stack = node_1;
	node_n_1->next = node_n;
	node_n->next = NULL;
	if (rx != NULL)
		ft_printf("%s\n", rx);
}

void	push_do_px(t_list_push **src, t_list_push **dest, char *px)
{
	t_list_push	*src_node_1;
	t_list_push	*dest_node_1;

	src_node_1 = (*src)->next;
	dest_node_1 = *src;
	if (*dest == NULL)
	{
		*dest = *src;
		(*dest)->next = NULL;
	}
	else
		push_lstadd_front(dest, dest_node_1);
	*src = src_node_1;
	ft_printf("%s\n", px);
}
