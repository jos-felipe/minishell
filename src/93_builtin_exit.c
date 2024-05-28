/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   93_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/28 14:51:49 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

// static void	mini_printenv(t_dict *dict);

int			mini_exit(t_token *arg, t_dict **dict)
{
	if (!arg)
		ft_printf("Hello World!");
	return (0);
}

/* static void	mini_printenv(t_dict *dict)
{
	t_dict	*cur;
	
	cur = ft_dictsort(dict);
	while (cur)
	{
		if (cur->value)
			ft_printf("%s=%s\n", cur->key, cur->value);
		else
			ft_printf("%s\n", cur->key);
		cur = cur->next;
	}
} */
