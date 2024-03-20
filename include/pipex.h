/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:04:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/20 17:19:03 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/includes/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_token
{
	char 	*token;
	struct s_token *next;
}	t_token;

typedef struct s_pipex
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
	char	**split_cmd_line;
	char	*pathname;
	t_token	*token_list;
}				t_pipex;

//  main.c functions prototype
int		main(int argc, char *argv[], char *envp[]);
void	ft_init(t_pipex *pipex);
void	ft_connect_fds(t_pipex *pipex);

//  02_launch_executable.c
void	mini_process_envp(t_pipex *pipex, char *envp[]);
void	mini_parse_readline(t_pipex *pipex);

// 02_utils.c
char	*mini_get_path(char *envp[]);
void	mini_trashman(t_list *lst_memory);
void	free_heap(t_list *lst_memory);
void	mini_free_split(char **split);
char	*mini_whereis(char *cmd, char *path);

//  safety.c functions prototype
void	ft_validate_user_inputs(int argc, char *argv[], char *envp[], \
t_pipex *pipex);
char	*ft_hacker_protection(char *cmd);
void	ft_safe_exit(t_pipex *pipex);

//  shell.c functions prototype
void	ft_tty1(t_pipex *pipex, char *envp[]);
void	ft_tty2(t_pipex *pipex, char *envp[]);
int		ft_get_exit_status(int exit_status);

#endif