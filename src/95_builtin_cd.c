/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   95_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/27 12:12:47 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int	mini_cd(t_token *arg, t_dict **dict)
{
	if (!arg->token)
		mini_go_home();
	ft_printf("%s\n", ft_dict_get_value(*dict, "PWD"));
	return (0);
}

void	mini_go_home(t_dict *dict)
{
	char	var[2];
	char	*old_path;
	
	old_path = ft_dict_get_value(dict, "OLDPWD");
	var[0] = "PWD";
	var[1] = ft_dict_get_value(dict, "HOME");
	ft_dict_update(dict, var);
	var[0] = "OLDPWD";
	var[1] = old_path;
	ft_dict_update(dict, var);
}