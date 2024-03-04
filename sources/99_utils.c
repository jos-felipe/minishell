/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:34:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/02/22 15:02:03 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_is_zero(char *str)
{
	while (*str)
	{
		if (*str != '0')
			return (0);
		str++;
	}
	if (*str == '\0')
		return (1);
	return (0);
}

void	free_heap(t_list *lst_memory)
{
	t_list	*tmp;

	while (lst_memory)
	{
		tmp = lst_memory;
		lst_memory = lst_memory->next;
		free(tmp->content);
		free(tmp);
	}
}

void	push_safe_exit(	int status, \
						t_list_push **a, \
						t_list_push **b, \
						t_bst **bst)
{
	if (a != NULL)
		push_lstclear(a);
	if (b != NULL)
		push_lstclear(b);
	if (bst != NULL)
		bst_free_all(*bst);
	if (status)
		ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(status);
}

void	push_lstclear(t_list_push **lst)
{
	t_list_push	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		free(*lst);
		*lst = aux;
	}
}

long	ft_atol(const char *nptr)
{
	long	sign;
	long	nb;

	sign = 1;
	nb = 0;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' || \
			*nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		nb = (*nptr - '0') + (nb * 10);
		nptr++;
	}
	return (nb * sign);
}
