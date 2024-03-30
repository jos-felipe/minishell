/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:48:39 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/30 12:08:18 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	mini_check_pipe_sintax(t_token *token_list)
{
	if (token_list->token[0] == '|')
	{
		ft_printf("bash: syntax error near unexpected token `|'\n");	
		return (1);
	}
	while (token_list)
	{
		if (token_list->token[0] == '|' && token_list->next == NULL)
		{
			ft_printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		token_list = token_list->next;
	}
	return (0);
}
void	mini_lstdelone(t_token *lst)
{
	if (lst && lst->token)
	{
		free(lst->token);
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

void	debug_print_list(t_token **head) // FOR DEBUG ONLY
{
	t_token *node;

	node = *head;
	while (node)
	{
		printf("token: %s\n", (char *)node->token);
		node = node->next;
	}
	printf("\n");
}