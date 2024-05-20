/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/20 15:21:43 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int		mini_unset(t_token *arg, t_dict **dict)
{
	if (!arg)
		return (0);
	ft_dictdel_entry(dict, arg->token);
	return (0);
}