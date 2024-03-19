/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_analysis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:44 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 13:05:59 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_analysis(t_pipex *mini)
{
	char	**analysis_list;

	analysis_list = mini->split_cmd_line;
	printf("%s | %s| %s | %s | %s | %s\n", analysis_list[0], analysis_list[1], analysis_list[2], analysis_list[3], analysis_list[4], analysis_list[5]);
	analysis_list = mini_get_in_and_output(analysis_list, mini->analysis);
	printf("%s | %s\n", analysis_list[0], analysis_list[1]);
	//analysis_list = mini_get_cmd_and_arg(analysis_list, mini->analysis);
}

char	**mini_get_in_and_output(char **analysis_list, t_analysis *analysis)
{
	char	**new_analysis_line_split;
	char	*new_analysis_line;
	int		redirect_type;

	new_analysis_line = NULL;
	while (*analysis_list)
	{
		redirect_type = search_redirect(*analysis_list);
		if (redirect_type)
			handle_redirect(analysis, *analysis_list++, redirect_type);
		else
		{
			if (new_analysis_line)
			{
				new_analysis_line = ft_strjoin(new_analysis_line, " ");
				new_analysis_line = ft_strjoin(new_analysis_line, *analysis_list);
			}
			else
				new_analysis_line = ft_strdup(*analysis_list);
		}
		analysis_list++;
	}
	new_analysis_line_split = ft_split(new_analysis_line, ' ');
	return (new_analysis_line_split);
}

int	search_redirect(char *analysis_str)
{
	int redirect_type;
	
	redirect_type = 0;
	if (analysis_str[0] == '>')
		redirect_type = 1;
	else if (analysis_str[0] == '<')
		redirect_type = 2;
	else if (analysis_str[0] == '>' && analysis_str[1] == '>')
		redirect_type = 3;
	return (redirect_type);
	
}

void	handle_redirect(t_analysis *analysis, char *analysis_str, int redirect_type)
{
	analysis_str = NULL;
	
	if (redirect_type == 1)
		analysis->output_fd = 3;
	else if (redirect_type == 2)
		analysis->input_fd = 3;
	else if (redirect_type == 3)
		analysis->append = 3;
}