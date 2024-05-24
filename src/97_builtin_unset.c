/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/23 13:46:31 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"
// #include "../include/dictionary.h"

// int		mini_unset(t_token *arg, t_dict **dict)
// {
// 	if (!arg)
// 		return (0);
// 	if (mini_valid_identifier(arg->token, dict, 0, 0))
// 		return (1);
// 	ft_dictdel_entry(dict, arg->token);
// 	return (0);
// }