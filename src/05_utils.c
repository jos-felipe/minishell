/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:47 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/21 19:28:13 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_lstdelone(t_token *lst)
{
	if (lst && lst->token)
	{
		free(lst->token);
		free(lst);
	}
}

t_token	*mini_lstnew(void *token)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->token = token;
	new_node->next = NULL;
	return (new_node);
}

void	mini_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_lstlast(*lst);
	last_node->next = new;
}

t_token	*mini_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	mini_free_token_list(t_token **lst_memory)
{
	t_token	*next;

	while (*lst_memory)
	{
		next = (*lst_memory)->next;
		free((*lst_memory)->token);
		free(*lst_memory);
		*lst_memory = next;
	}
	*lst_memory = NULL;
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

void	debug_print_list(t_token **head) // FOR DEBUG ONLY
{
	t_token *node;

	node = *head;
	while (node)
	{
		printf("%s\n", (char *)node->token);
		node = node->next;
	}
	printf("\n");
}

