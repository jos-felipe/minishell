/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_get_cmd_path.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:14:26 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/20 14:17:04 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_get_cmd_path
{
	char	*cmd_name;
	char	*path;
	char	*part_path;
	char	**splited_path;
	int		i;
}	t_get_cmd_path;