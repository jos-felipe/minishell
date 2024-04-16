/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_men.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:01:36 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/16 13:02:15 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftplus.h"
#include "../include/minishell.h"

char	*ft_substr_mem(char *str, int start, int len)
{
	char	*substr;
	
	substr = ft_substr(str, start, len);
	ft_collect_mem(substr);
	return (str);
}