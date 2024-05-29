/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:23:01 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/29 11:41:35 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_is_valid_heredoc(t_token *token_node)
{
	if (token_node && token_node->gender == WORD)
		return (1);
	return (0);
}

void	mini_handle_heredoc(t_mini *mini, t_token *token_node)
{
	char	*line;
	char	*word;

	line = NULL;
	word = token_node->token;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s\')", word);
			free(line);
			break;
		}
		else if (!ft_strncmp(line, word, ft_strlen(word)))
		{
			free(line);
			break ;
		}
		// ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
	// close(pipe_fd[1]);
	// pipex->fd_in = pipe_fd[0];
}