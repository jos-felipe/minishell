/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   96_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/27 16:41:19 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int		mini_pwd(t_token *arg, t_dict **dict)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	ft_collect_mem_env(cwd);
	ft_printf("%s\n", cwd);
	return (0);
}
