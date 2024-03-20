/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:47 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/20 17:14:01 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_lstdelone(t_cmd_line_list *lst)
{
	if (lst && lst->content)
	{
		free(lst->content);
		free(lst);
	}
}

t_cmd_line_list	*mini_lstnew(void *content)
{
	t_cmd_line_list	*new_node;

	new_node = malloc(sizeof(t_cmd_line_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->is_valid = 1;
	new_node->next = NULL;
	return (new_node);
}

void	mini_lstadd_back(t_cmd_line_list **lst, t_cmd_line_list *new)
{
	t_cmd_line_list	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_lstlast(*lst);
	last_node->next = new;
}

t_cmd_line_list	*mini_lstlast(t_cmd_line_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
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

void	debug_print_list(t_cmd_line_list **head) // FOR DEBUG ONLY
{
	t_cmd_line_list *node;

	node = *head;
	while (node)
	{
		printf("%s, %d | ", (char *)node->content, node->is_valid);
		node = node->next;
	}
	printf("\n");
	
}
