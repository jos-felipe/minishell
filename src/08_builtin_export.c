/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/16 14:50:09 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_export(t_token *arg, t_dict **env_list)
{
	int		exit_status;
	int		tmp;
	t_token	*cur;

	exit_status = 0;
	cur = arg;
	while (cur)
	{	
		tmp = mini_env_identifier(arg->token, env_list, 0, 0);
		if (tmp)
			exit_status = tmp;
		cur = cur->next;
	}
	return (exit_status);
}
