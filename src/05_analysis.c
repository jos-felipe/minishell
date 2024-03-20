/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_analysis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:44 by gfantoni          #+#    #+#             */
/*   Updated: 2024/03/19 17:32:48 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_analysis(t_pipex *mini)
{
	t_cmd_line_list	*analysis_list;
	
	analysis_list = mini_fill_analysis_list(mini->split_cmd_line);

	debug_print_list(&analysis_list); // FOR DEBUG ONLY
	mini_get_in_and_output(&analysis_list, mini->analysis);
	debug_print_list(&analysis_list); // FOR DEBUG ONLY
	// mini_get_cmd_and_arg(analysis_list, mini->analysis);
}

t_cmd_line_list *mini_fill_analysis_list(char **split_cmd_line)
{
	t_cmd_line_list	*analysis_list;

	analysis_list = NULL;
	while (*split_cmd_line)
	{
		if (analysis_list)
			mini_lstadd_back(&analysis_list, mini_lstnew(*split_cmd_line));
		else
			analysis_list = mini_lstnew(*split_cmd_line);
		split_cmd_line++;
	}
	return (analysis_list);
}

void	mini_get_in_and_output(t_cmd_line_list **analysis_list, t_analysis *analysis)
{
	int					redirect_type;
	t_cmd_line_list		*temp;
	
	temp = *analysis_list;
	while (temp)
	{
		redirect_type = search_redirect(temp->content);
		if (redirect_type)
		{
			handle_redirect(analysis, temp->next->content, redirect_type);
			temp->is_valid = 0;
			if (temp->next)
				temp->next->is_valid = 0;
		}
		temp = temp->next;
	}
}

int	search_redirect(char *analysis_content)
{
	int redirect_type;
	
	redirect_type = 0;
	if (analysis_content[0] == '>')
		redirect_type = 1;
	else if (analysis_content[0] == '<')
		redirect_type = 2;
	else if (analysis_content[0] == '>' && analysis_content[1] == '>')
		redirect_type = 3;
	return (redirect_type);
	
}

void	handle_redirect(t_analysis *analysis, char* analysis_str, int redirect_type)
{
	analysis_str = NULL;
	
	if (redirect_type == 1)
		analysis->output_fd = 3;
	else if (redirect_type == 2)
		analysis->input_fd = 3;
	else if (redirect_type == 3)
		analysis->append = 3;
}

// void	mini_get_cmd_and_arg(t_cmd_line_list *analysis_list, t_analysis *analysis)
// {
// 	int					redirect_type;
// 	t_cmd_line_list		*temp;
	
// 	temp = *analysis_list;
// 	while (temp)
// 	{
// 		redirect_type = search_redirect(temp->content);
// 		if (redirect_type)
// 		{
// 			handle_redirect(analysis, temp->next->content, redirect_type);
// 			temp->is_valid = 0;
// 			if (temp->next)
// 				temp->next->is_valid = 0;
// 		}
// 		temp = temp->next;
// 	}
	
}

