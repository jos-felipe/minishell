/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_check_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:25:54 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/26 16:48:23 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bst.h"

int	bst_verify(t_bst *node, int minkey, int maxkey)
{
	if (node == NULL)
		return (TRUE);
	if (node->key < minkey || node->key > maxkey)
		return (FALSE);
	return (bst_verify(node->left_child, minkey, node->key - 1)
		&& bst_verify(node->right_child, node->key + 1, maxkey));
}

int	bst_is_member(t_bst *node, int find_key)
{
	if (node == NULL)
		return (FALSE);
	else if (find_key > node->key)
		return (bst_is_member(node->right_child, find_key));
	else if (find_key < node->key)
		return (bst_is_member(node->left_child, find_key));
	else
		return (TRUE);
}

int	bst_num_nodes(t_bst *node)
{
	if (node == NULL)
		return (0);
	else
		return (1 + bst_num_nodes(node->right_child)
			+ bst_num_nodes(node->left_child));
}
