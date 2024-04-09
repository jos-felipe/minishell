/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/09 14:08:40 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

enum e_token_gender
{
	WORD,
	OPERATOR
};

enum e_token_specie
{
	UNDEFINED = -1,
	OUT_REDIRECT,
	APPEND,
	IN_REDIRECT,
	HERE_DOC,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	PIPE
};

typedef struct s_token
{
	char 					*token;
	enum e_token_gender		gender;
	enum e_token_specie		specie;
	struct s_token 			*next;
	struct s_token 			*prev;
}	t_token;

typedef struct s_mini
{
	char	*path;
	t_list	*lst_memory;
	int		status;
	char	*cmd_line;
	char	*pathname;
	t_token	*token_list;
	t_token	**commands;
	int		syntax_error;
}				t_mini;

// trashman.c
void    *allocate_mem(size_t nmemb, size_t size);
void    collect_mem(void *content);
t_list    **get_mem_address(void);
void	mini_free_trashman(t_list **lst_memory);

// 00_main.c
int			main(int argc, char *argv[], char *envp[]);

// 00_utils.c
void		mini_ctrl_d_exit(t_mini *mini);


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
void	mini_trashman(t_list **lst_memory);

// 04_special_parameter.c
void	mini_special_parameter(t_mini *mini);
char	*mini_expand(char c, t_mini *mini);
int		ft_get_exit_status(int exit_status);

// 05_tokenizer.c
void	mini_tokenizer(t_mini *mini);
int		mini_automaton(char *str, t_token **token_list, int start, int state);
int		mini_get_next_state(int state, int column);
int		mini_get_column(char c);
int		mini_is_back_state(int num);
int		mini_is_error_state(int num);
int		mini_is_end_state(int num);
void	mini_print_sintax_error_message(int state);
int		mini_check_pipe_sintax(t_token *token_list);

// 05_utils.c
void	mini_lstdelone(t_token *lst);
t_token	*mini_token_lstnew(void *token, int state);
void	mini_token_lstadd_back(t_token **lst, t_token *new);
t_token	*mini_lstlast(t_token *lst);
void	mini_free_token_list(t_token **lst_memory);
void	mini_get_token_gender(int state, t_token *token);
void	mini_get_token_specie(int state, t_token *token);
void	debug_print_split(char **str); // FOR DEBUG ONLY
void	debug_print_list(t_token **head); // FOR DEBUG ONLY

// 06_parser.c
void	mini_parser(t_mini *mini);
void	mini_fill_cmd_array(t_mini  *mini);
int		mini_count_nbr_pipes(t_token *token_list);
t_token	*mini_t_token_dup(t_token *t);

// 06_utils.c
void	debug_print_array_list(t_mini *mini); // FOR DEBUG ONLY
void	debug_print_parse_list(t_token **head); // FOR DEBUG ONLY

// 07_expansion.c
void	mini_expansion(t_mini *mini);
void	mini_token_expansion(t_mini *mini, int i);
char	*mini_sep_exp_join(t_mini *mini, char *token);
char	*mini_search_and_replace(t_mini *mini, char *sub_token);

// 07_utils_1.c
void	mini_init_env_list(t_mini *mini, char *envp[]);
char	*mini_substr_pointer(char *begin, char *end);
t_env	*mini_env_lstnew(char **var);
void	mini_env_lstadd_back(t_env **lst, t_env *new);
t_env	*mini_env_lstlast(t_env *lst);
char	*mini_sub_token_join(t_list *sub_token_lst);

// 07_utils_2.c
void	mini_sub_tokenizier(char *str, t_list **sub_token_lst, int start, int state);
int	mini_get_next_state(int state, int column);
int	mini_get_column(char c);
int is_one_back_state(int state);
int is_two_back_state(int state);





#endif