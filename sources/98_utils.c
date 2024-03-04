/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   98_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:54:54 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/22 19:21:57 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_list_push	*push_lstnew(int nbr)
{
	t_list_push	*new_node;

	new_node = malloc(sizeof(t_list_push));
	if (new_node == NULL)
		return (NULL);
	new_node->value = nbr;
	new_node->index = 0;
	new_node->position = -1;
	new_node->target_pos = -1;
	new_node->cost_a = INT_MAX;
	new_node->cost_b = INT_MAX;
	new_node->next = NULL;
	return (new_node);
}

void	push_lstadd_back(t_list_push **lst, t_list_push *new)
{
	t_list_push	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = push_lstlast(*lst);
	last_node->next = new;
}

t_list_push	*push_lstlast(t_list_push *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	push_lstprintf_index(t_list_push *lst)
{
	int	index;

	while (lst)
	{
		index = lst->index;
		ft_printf("%d ", index);
		lst = lst->next;
	}
}
