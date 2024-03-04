/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_user_input_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:43:20 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/26 16:19:09 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_pre_user_input_validation(int *argc, char ***argv)
{
	if (*argc == 2)
		push_user_input_validation_split(argc, argv);
}

void	push_user_input_validation(int argc, char *argv[], t_bst **bst)
{
	if (argc == 1)
		exit(1);
	ft_int(argc, argv, bst);
	return ;
}

void	ft_int(int argc, char *argv[], t_bst **bst)
{
	int		i;
	long	nbr;
	int		was_inserted;

	was_inserted = FALSE;
	i = 1;
	while (i < argc)
	{
		if (!only_digit(argv[i]))
			push_error(bst);
		nbr = ft_atol(argv[i]);
		if (ft_int_overflow(nbr))
			push_safe_exit(1, NULL, NULL, bst);
		(*bst) = push_bst_insert(bst, *bst, (int)nbr, &was_inserted);
		i++;
	}
}

t_bst	*push_bst_insert(t_bst **head, t_bst *node, int key, int *was_inserted)
{
	*was_inserted = FALSE;
	if (node == NULL)
	{
		*was_inserted = TRUE;
		return (bst_create_node(key));
	}
	if (key == node->key)
		push_error(head);
	else if (key > node->key)
		node->right_child
			= push_bst_insert(head, node->right_child, key, was_inserted);
	else if (key < node->key)
		node->left_child
			= push_bst_insert(head, node->left_child, key, was_inserted);
	return (node);
}

void	push_user_input_validation_split(int *argc, char ***argv)
{
	char	*str_holder;

	if (push_count_words((*argv)[1], ' ') <= 1)
		return ;
	else
	{
		str_holder = ft_strjoin("placeholder ", (*argv)[1]);
		*argc = push_count_words(str_holder, ' ');
		*argv = ft_split(str_holder, ' ');
		free(str_holder);
	}
}
