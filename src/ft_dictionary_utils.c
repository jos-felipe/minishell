/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dictionary_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:44:30 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/02 11:50:41 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dictionary.h"

void	ft_dict_print(t_dict *dict)
{
	t_dict	*cur;
	
	cur = dict;
	while (cur)
	{
		ft_printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}