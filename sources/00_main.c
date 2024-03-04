/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:11 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/26 09:18:30 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char *argv[])
{
	t_bst		*bst;
	t_list_push	*a;
	t_list_push	*b;
	int			rotations[2];

	bst = NULL;
	a = NULL;
	b = NULL;
	push_pre_user_input_validation(&argc, &argv);
	push_user_input_validation(argc, argv, &bst);
	push_fill_stack(&a, argc, argv);
	push_free_split(argv);
	if (push_is_sorted(a))
		push_safe_exit(0, &a, &b, &bst);
	push_bst_indexing(&bst);
	push_lst_indexing(a, bst);
	push_only_swap_or_tiny_sort(&a, &b, &bst);
	push_all_save_three(&a, &b);
	push_tiny_sort(&a);
	push_target_pos(a, b);
	push_comp_cost(a, b);
	push_cheapest_move(b, rotations);
	push_sort(&a, &b, rotations);
	push_swap(&a, &b, rotations);
	push_safe_exit(0, &a, &b, &bst);
}
