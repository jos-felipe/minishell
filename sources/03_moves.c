/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:03:18 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/23 12:16:58 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_gateway(enum e_op op, t_list_push **a, t_list_push **b)
{
	if (op == SA)
		push_do_sx(a, "sa");
	else if (op == SB)
		push_do_sx(b, "sb");
	else if (op == SS)
		push_do_ss(a, b, "ss");
	else if (op == RA)
		push_do_rx(a, "ra");
	else if (op == RB)
		push_do_rx(b, "rb");
	else if (op == RR)
		push_do_rr(a, b, "rr");
	else if (op == RRA)
		push_do_rrx(a, "rra");
	else if (op == RRB)
		push_do_rrx(b, "rrb");
	else if (op == RRR)
		push_do_rrr(a, b, "rrr");
	else if (op == PA)
		push_do_px(b, a, "pa");
	else if (op == PB)
		push_do_px(a, b, "pb");
}

t_list_push	*push_lst_n_1(t_list_push *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

void	push_lstadd_front(t_list_push **lst, t_list_push *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
