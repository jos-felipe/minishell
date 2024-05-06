/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictionary_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:44:30 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/02 12:54:50 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dictionary.h"

void	ft_dict_print(t_dict *dict)
{
	t_dict	*cur;
	
	cur = dict;
	while (cur)
	{
		if (cur->value)
			ft_printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			ft_printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
}

t_dict	*ft_dictsort(t_dict *dict)
{
	t_dict	*header;
	char	*key;
	char	*value;

	header = dict;
	while (dict->next)
	{
		if (ft_strncmp(dict->key, dict->next->key, ft_strlen(dict->next->key)) <= 0)
			dict = dict->next;
		else
		{
			key = dict->key;
			value = dict->value;
			dict->key = dict->next->key;
			dict->value = dict->next->value;
			dict->next->key = key;
			dict->next->value = value;
			dict = header;
		}
	}
	return (header);
}
