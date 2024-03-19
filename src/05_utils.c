/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:47 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 16:31:25 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_lstdelone(t_list *lst)
{
	if (lst && lst->content)
	{
		free(lst->content);
		free(lst);
	}
}

void	debug_print_split(char **str) // FOR DEBUG ONLY
{
	while (*str)
	{
		printf("%s | ", *str);
		str++;
	}
	printf("\n");
}

void	debug_print_list(t_list **head) // FOR DEBUG ONLY
{
	t_list *node;

	node = *head;
	while (node)
	{
		printf("%s | ", (char *)node->content);
		node = node->next;
	}
	printf("\n");
	
}
