/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   96_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/22 15:17:29 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int		mini_pwd(t_token *arg, t_dict **dict)
{
	ft_printf("%s\n", ft_dict_get_value(*dict, "PWD"));
	return (0);
}