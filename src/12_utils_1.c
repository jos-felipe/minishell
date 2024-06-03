/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:02:29 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/03 11:22:16 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/builtins.h"

t_token	*mini_exec_interface(char **cmd_exec)
{
	t_token	*token_lst;
	int		i;

	token_lst = NULL;
	i = 0;
	while (cmd_exec && cmd_exec[i])
		mini_token_lstadd_back(&token_lst, mini_token_lstnew(cmd_exec[i++], 0));
	return (token_lst);
}