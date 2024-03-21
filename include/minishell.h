/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/21 19:33:23 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_token
{
	char 	*token;
	struct s_token *next;
}	t_token;

typedef struct s_mini
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	int		pid1;
	int		pid2;
	char	*path;
	char	**argv1;
	char	**argv2;
	char	*fn1;
	char	*fn2;
	t_list	*lst_memory;
	int		status;
	char	*cmd_line;
	char	*pathname;
	t_token	*token_list;
}				t_mini;

// 00_main.c
int			main(int argc, char *argv[], char *envp[]);

// 01_prompt.c
void		mini_prompt(t_mini *mini);

// 01_utils.c
void		mini_init(t_mini *pipex);
void		mini_trashman_collector(t_list **list_memory, void *trash);
void		mini_safe_exit(t_mini *mini);

// 02_ctrl_signal.c
void	mini_ctrl_signal(void);
void	sig_handler(int signum);

// 03_process_envp.c
void	mini_process_envp(t_mini *pipex, char *envp[]);
void	mini_execute(t_mini *mini);

// 03_utils
char	*mini_get_path(char *envp[]);
void	free_heap(t_list *lst_memory);
void	mini_free_split(char **split);
char	*mini_whereis(char *cmd, char *path);
void	mini_trashman(t_list *lst_memory);

// 04_special_parameter.c
void	mini_special_parameter(t_mini *mini);
char	*mini_expand(char c, t_mini *mini);
int		ft_get_exit_status(int exit_status);

// 05_analysis.c
void	mini_tokenizer(t_mini *mini);
void	mini_automaton(char *str, t_token **token_list, int start, int state);
int		mini_get_next_state(int state, int column);
int		mini_get_column(char c);
int		mini_is_back_state(int num);
int		mini_is_error_state(int num);
int		mini_is_end_state(int num);

// 05_utils.c
void	mini_lstdelone(t_token *lst);
t_token	*mini_lstnew(void *token);
void	mini_lstadd_back(t_token **lst, t_token *new);
t_token	*mini_lstlast(t_token *lst);
void	mini_free_token_list(t_token **lst_memory);
void	debug_print_split(char **str); // FOR DEBUG ONLY
void	debug_print_list(t_token **head); // FOR DEBUG ONLY


#endif