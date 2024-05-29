/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:23:01 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/29 16:47:36 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *debug_join_check(t_token *token_node);
static void mini_init_hd(t_mini *hd, char *line);
static void mini_hd_tokenizer(t_mini *hd);

char	*mini_hd_expansion(char *line)
{
	t_mini	hd;
	char	*exp_line;
	
	if (!ft_strchr(line, '$'))
		return (line);
	mini_init_hd(&hd, line);
	mini_hd_tokenizer(&hd);
	// mini_hd_parser(&hd);
	// mini_expansion(&hd);
	// exp_line = mini_join_exp_list(&hd);
	exp_line = debug_join_check(hd.token_list);
	return (exp_line);
}

static char *debug_join_check(t_token *token_node)
{
	char *str;
	int i = 0;

	str = NULL;
	while (token_node)
	{
		i++;
		token_node = token_node->next;
	}
	return (ft_itoa(i));
}

static void mini_init_hd(t_mini *hd, char *line)
{
	hd->path = NULL;
	hd->lst_memory = NULL;
	hd->status = 0;
	hd->cmd_line = line;
	hd->pathname = NULL;
	hd->token_list = NULL;
	hd->env_list = NULL;
	hd->cmd_exec_list = NULL;
	hd->syntax_error = 0;
	hd->mini_environ = NULL;
	hd->hd_file_index = 0;
}

static void mini_hd_tokenizer(t_mini *hd)
{
	t_dfa dfa;
	
	mini_init_dfa(&dfa);
	mini_automaton(hd, &dfa);
}


