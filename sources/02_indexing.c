/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_indexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:05:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/26 09:18:20 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_fill_stack(t_list_push **a, int argc, char *argv[])
{
	int		i;
	long	nbr;

	i = 1;
	while (i < argc)
	{
		nbr = ft_atol(argv[i]);
		push_lstadd_back(a, push_lstnew(nbr));
		i++;
	}
}

int	push_bst_is_member(t_bst *node, int find_key)
{
	if (node == NULL)
		return (0);
	else if (find_key > node->key)
		return (push_bst_is_member(node->right_child, find_key));
	else if (find_key < node->key)
		return (push_bst_is_member(node->left_child, find_key));
	else
		return (node->index);
}

void	push_lst_indexing(t_list_push *a, t_bst *bst)
{
	int	key;

	while (a)
	{
		key = a->value;
		a->index = push_bst_is_member(bst, key);
		a = a->next;
	}
}

void	push_bst_indexing(t_bst **bst)
{
	push_bst_in_order_static(*bst, 0);
	return ;
}

void	push_bst_in_order_static(t_bst *node, int layer)
{
	static int	index;

	if (layer == 0)
		index = 1;
	if (node == NULL)
		return ;
	push_bst_in_order_static(node->left_child, layer + 1);
	node->index = index;
	index++;
	push_bst_in_order_static(node->right_child, layer + 1);
}
