/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/26 17:06:31 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../lib/includes/libft.h"
# include "bst.h"

enum e_op
{
	SA,
	SB,
	SS,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	PA,
	PB
};

typedef struct s_list_push
{
	int					value;
	int					index;
	int					position;
	int					target_pos;
	int					cost_a;
	int					cost_b;
	struct s_list_push	*next;
}	t_list_push;

// 01_user_input_validation.c
void		push_user_input_validation(int argc, char *argv[], t_bst **bst);
void		ft_int(int argc, char *argv[], t_bst **bst);
t_bst		*push_bst_insert(t_bst **head, t_bst *node,
				int insert_key, int *was_inserted);
void		push_user_input_validation_split(int *argc, char ***argv);
void		push_pre_user_input_validation(int *argc, char ***argv);

// 02_indexing.c
void		push_fill_stack(t_list_push **a, int argc, char *argv[]);
int			push_bst_is_member(t_bst *node, int find_key);
void		push_lst_indexing(t_list_push *a, t_bst *bst);
void		push_bst_indexing(t_bst **bst);
void		push_bst_in_order_static(t_bst *node, int index);

// 03_moves.c
void		push_gateway(enum e_op op, t_list_push **a, t_list_push **b);
void		push_lstadd_front(t_list_push **lst, t_list_push *new);
t_list_push	*push_lst_n_1(t_list_push *lst);

// 03_do_moves.c
void		push_do_sx(t_list_push **stack, char *sx);
void		push_do_rrx(t_list_push **stack, char *rrx);
void		push_do_rx(t_list_push **stack, char *rx);
void		push_do_px(t_list_push **src, t_list_push **dest, char *px);

// 04_pre_sort.c
void		push_all_save_three(t_list_push **a, t_list_push **b);
void		push_tiny_sort(t_list_push **a);
void		push_only_swap_or_tiny_sort(t_list_push **a, t_list_push **b,
				t_bst **bst);

// 05_target_position.c
void		push_target_pos(t_list_push *a, t_list_push *b);
int			push_target_comp(int b_index, t_list_push *a);
int			push_target_min(t_list_push *a);
void		push_get_positon(t_list_push *node);

// 06_comp_cost.c
void		push_comp_cost(t_list_push *a, t_list_push *b);

// 07_cheapest_move.c
void		push_cheapest_move(t_list_push *b, int *rotations);

// 08_sort.c
void		push_sort(t_list_push **a, t_list_push **b, int *rotations);
void		push_double_rotation(t_list_push **a,
				t_list_push **b, int *rotations);
void		push_single_rot_a(t_list_push **a, int *rotation);
void		push_single_rot_b(t_list_push **b, int *rotation);

// 09_push_swap.c
void		push_swap(t_list_push **a, t_list_push **b, int *rotations);

// 10_dial.c
void		push_dial(t_list_push **a);

// 99_utils.c
int			ft_is_zero(char *str);
void		free_heap(t_list *lst_memory);
void		push_safe_exit(	int status, \
						t_list_push **a, \
						t_list_push **b, \
						t_bst **bst);
void		push_lstclear(t_list_push **lst);
long		ft_atol(const char *nptr);

// 99_2_utils.c
int			ft_int_overflow(long nbr);
int			only_digit(char *str);
int			push_count_words(char const *s, char sep);
void		push_free_split(char **split);
void		push_error(t_bst **head);

// 98_utils.c
t_list_push	*push_lstnew(int nbr);
void		push_lstadd_back(t_list_push **lst, t_list_push *new);
t_list_push	*push_lstlast(t_list_push *lst);
void		push_lstprintf_index(t_list_push *lst);

// 97_utils.c
void		push_do_rrr(t_list_push **a, t_list_push **b, char *rrr);
void		push_do_rr(t_list_push **a, t_list_push **b, char *rr);
void		push_do_ss(t_list_push **a, t_list_push **b, char *ss);
void		push_lstprintf_value(t_list_push *lst);

// 96_utils.c
int			push_is_sorted(t_list_push *node);
int			push_lstsize(t_list_push *lst);

// 95_utils.c
void		push_lstprintf_target_pos(t_list_push *lst);

// 94_utils.c
void		push_lstprintf_cost(t_list_push *lst);

// 93_utils.c
int			push_abs(int n);

// 92_utils.c

// 91_utils.c

// 90_utils.c

#endif