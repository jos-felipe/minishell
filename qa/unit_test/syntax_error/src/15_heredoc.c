/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:23:01 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/30 17:39:37 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int mini_create_file(t_mini *mini, t_token *token_node);

int	mini_is_valid_heredoc(t_token *token_node)
{
	if (token_node && token_node->gender == WORD)
		return (1);
	return (0);
}

void	mini_handle_heredoc(t_mini *mini, t_token *token_node)
{
	char	*line;
	char	*exp_line;
	char	*word;
	int		hd_file_fd;

	word = token_node->token;
	hd_file_fd = mini_create_file(mini, token_node);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s\')\n", word);
			free(line);
			close(hd_file_fd);
			break ;
		}
		else if (!ft_strncmp(line, word, ft_strlen(line) + ft_strlen(word)))
		{
			free(line);
			close(hd_file_fd);
			break ;
		}
		if (token_node->was_quoted == 107 || token_node->was_quoted == 108)
			exp_line = line;
		else
			exp_line = mini_hd_expansion(line);
		ft_printf_fd(hd_file_fd, "%s\n", exp_line);
		free(line);
	}
	// close(pipe_fd[1]);
	// pipex->fd_in = pipe_fd[0];
}

static int mini_create_file(t_mini *mini, t_token *token_node)
{
	int 		fd;
	char		*file_index_str;
	char		*file_name;
	
	file_index_str = ft_itoa(mini->hd_file_index);
	file_name = ft_strjoin("heredoc", file_index_str);
	ft_collect_mem(file_name);
	token_node->token = file_name;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 420);
	free(file_index_str);
	mini->hd_file_index++;
	return (fd);
}