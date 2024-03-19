/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:47 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 14:13:39 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	debug_print_split(char **analysis_list) // FOR DEBUG ONLY
{
	while (*analysis_list)
	{
		printf("%s | ", *analysis_list);
		analysis_list++;
	}
	printf("\n");
}