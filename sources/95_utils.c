/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   95_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:05:24 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/22 15:05:25 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_lstprintf_target_pos(t_list_push *lst)
{
	int	target_pos;

	while (lst)
	{
		target_pos = lst->target_pos;
		ft_printf("%d ", target_pos);
		lst = lst->next;
	}
	ft_printf("\n");
}
