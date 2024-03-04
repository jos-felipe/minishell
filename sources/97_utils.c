/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:57:08 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/22 14:58:19 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_do_rr(t_list_push **a, t_list_push **b, char *rr)
{
	push_do_rx(a, NULL);
	push_do_rx(b, NULL);
	ft_printf("%s\n", rr);
}

void	push_do_rrr(t_list_push **a, t_list_push **b, char *rrr)
{
	push_do_rrx(a, NULL);
	push_do_rrx(b, NULL);
	ft_printf("%s\n", rrr);
}

void	push_do_ss(t_list_push **a, t_list_push **b, char *ss)
{
	push_do_sx(a, NULL);
	push_do_sx(b, NULL);
	ft_printf("%s\n", ss);
}

void	push_lstprintf_value(t_list_push *lst)
{
	int	value;

	while (lst)
	{
		value = lst->value;
		ft_printf("%d ", value);
		lst = lst->next;
	}
	ft_printf("\n");
}
