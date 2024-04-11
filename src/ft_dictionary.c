/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictionary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:26:06 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/11 15:15:14 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dictionary.h"
#include "../include/minishell.h"

t_dict	*ft_dictnew(char **var)
{
	t_dict	*new_entry;

	new_entry = malloc(sizeof(t_dict));
	collect_mem(new_entry);
	if (new_entry == NULL)
		return (NULL);
	new_entry->key = var[0];
	new_entry->value = var[1];
	new_entry->next = NULL;
	return (new_entry);
}

void	ft_dictadd_back(t_dict **dict, t_dict *new_entry)
{
	t_dict	*last_node;

	if (*dict == NULL)
	{
		*dict = new_entry;
		return ;
	}
	last_node = ft_dictlast(*dict);
	last_node->next = new_entry;
}

t_dict	*ft_dictlast(t_dict *dict)
{
	if (dict == NULL)
		return (NULL);
	while (dict->next != NULL)
		dict = dict->next;
	return (dict);
}