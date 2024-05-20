/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/20 14:39:45 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int		mini_unset(t_token *arg)
{
	if (!arg)
		return (0);
	return(ft_printf("arg: %s", arg->token));
}