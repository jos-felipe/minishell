/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:38:07 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/30 11:48:08 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*mini_token_lstnew(void *token, int state)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->token = token;
	mini_get_token_gender(state, new_node);
	mini_get_token_specie(state, new_node);
	new_node->next = NULL;
	new_node->prev = NULL;
	collect_mem(new_node);
	return (new_node);
}

void	mini_get_token_gender(int state, t_token *token)
{
	token->gender = OPERATOR;
	if (state == 100)
		token->gender = WORD;
}

void	mini_get_token_specie(int state, t_token *token)
{
	if (state == 100)
		token->specie = UNDEFINED;
	else if (state == 101)
		token->specie = OUT_REDIRECT;
	else if (state == 102)
		token->specie = APPEND;
	else if (state == 103)
		token->specie = IN_REDIRECT;
	else if (state == 104)
		token->specie = HERE_DOC;
	else if (state == 105)
		token->specie = PIPE;
}

void	mini_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_lstlast(*lst);
	last_node->next = new;
	new->prev = last_node;
}

t_token	*mini_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}