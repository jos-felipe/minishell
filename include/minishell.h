/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:52:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/22 15:00:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "dictionary.h"
# include "trashman.h"
# include "trashman_env.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

#define NULL_CHAR 666

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

typedef struct s_dfa
{
	char 	*value;
	int		size;
	int		start;
	int		state;
	int		quote;
	int		i;
}	t_dfa;

typedef struct s_token
{
	char 					*token;
	enum e_token_gender		gender;
	enum e_token_specie		specie;
	struct s_token 			*next;
	struct s_token 			*prev;
}	t_token;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_sub_token
{
	char				*content;
	struct s_sub_token	*next;
}				t_sub_token;

typedef struct s_cmd
{
	int				input_fd;
	int 			output_fd;
	int 			read_pipe;
	int 			write_pipe;
	int				nbr_of_words;
	char			**cmd_exec;
	char			*cmd_path;
	int				pid;
	struct s_cmd 	*next;
}		t_cmd;

typedef struct s_mini
{
	char	*path;
	t_list	*lst_memory;
	int		status;
	char	*cmd_line;
	char	*pathname;
	t_token	*token_list;
	t_token	**commands;
	t_dict	*env_list;
	t_cmd 	*cmd_exec_list;
	int		syntax_error;
}				t_mini;

// 00_utils.c
void		mini_ctrl_d_exit();

// 01_prompt.c
void		mini_prompt(t_mini *mini);

// 01_utils.c
void		mini_init(t_mini *pipex);
void		mini_trashman_collector(t_list **list_memory, void *trash);
// void		mini_safe_exit(t_mini *mini);

// 02_ctrl_signal.c
void	mini_ctrl_signal(void);
void	sig_handler(int signum);

// 03_process_envp.c
// void	mini_process_envp(t_mini *pipex, char *envp[]);
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
void	mini_init_dfa(t_dfa *dfa);
void	mini_automaton(t_mini *mini, t_dfa *dfa);
int		mini_get_next_state(int state, int column);
int		mini_get_column(char c);

// 05_utils_1.c
int		mini_is_end_state(int num);
void	mini_syntonize_index(t_dfa *dfa);
int		mini_is_back_state(int num);
int		mini_is_quote_state(int num);
int		mini_is_error_state(int num);

// 05_utils_2.c
void	mini_print_sintax_error_message(int state);
void	mini_cut_string(t_mini *mini, t_dfa *dfa);
void	mini_check_pipe_sintax(t_mini *mini, t_token *token_list);
void	mini_check_consecutive_op_sintax(t_mini *mini, t_token *token_list);
void	mini_check_pipe_space_pipe_sintax(t_mini *mini, t_token *token_list);

// 05_utils_3.c
t_token	*mini_token_lstnew(void *token, int state);
void	mini_get_token_gender(int state, t_token *token);
void	mini_get_token_specie(int state, t_token *token);
void	mini_token_lstadd_back(t_token **lst, t_token *new);
t_token	*mini_lstlast(t_token *lst);

// 05_utils_4.c
void	mini_free_token_list(t_token **lst_memory);
void	mini_lstdelone(t_token *lst);
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
char	*mini_get_dollar_sign(t_mini *mini, char *sub_token);
int		mini_has_invalid_char(char *sub_token);
char	*mini_expand_with_invalid(t_mini *mini, char *sub_token);
int		mini_is_invalid_char(char c);
char	*mini_str_after_invalid_char(char *sub_token);
char	*mini_str_before_invalid_char(char *sub_token);
char	*ft_strjoin_expansion(char const *s1, char const *s2);

// 07_utils_1.c
void	mini_getenv(t_mini *mini);
int		mini_strchr_index(char *str, char c);
char	*mini_sub_token_join(t_sub_token *sub_token_lst);

// 07_utils_2.c
void	mini_sub_tokenizier(char *str, t_sub_token **sub_token_lst, int start, int state);
int		mini_exp_get_next_state(int state, int column);
int		mini_exp_get_column(char c);
int		is_one_back_state(int state);
int		is_two_back_state(int state);

// 07_utils_3.c
t_sub_token	*mini_sub_token_lstnew(char *content);
t_sub_token	*mini_sub_token_lstlast(t_sub_token *lst);
void		mini_sub_token_lstadd_back(t_sub_token **lst, t_sub_token *new);

// 08_redirect.c
void	mini_redirect(t_mini *mini);
void	mini_find_redirect(t_mini *mini, int i);
void	mini_handle_out_redir(t_cmd *cmd_node, char *file);
void	mini_handle_in_redir(t_cmd *cmd_node, char *file);
void	mini_handle_append_redir(t_cmd *cmd_node, char *file);

// 08_utils_1.c
t_cmd	*mini_redir_lstnew(void);
void	mini_redir_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*mini_redir_lstlast(t_cmd *lst);

// 09_execute.c
void	mini_execute(t_mini *mini);
void	mini_build_cmd_exec(t_mini *mini);
void	mini_count_cmd_exec_words(t_token *token_node, t_cmd *cmd_exec_node);
void	mini_unite_cmd_exec_words(t_token *token_node, t_cmd *cmd_exec_node);
void	mini_match_cmd_exec_word(char *token, t_cmd *cmd_exec_node, int i);

// 10_get_cmd_path.c
void	mini_get_cmd_exec_path(t_mini *mini);
char	*mini_get_cmd_path(t_cmd *cmd_exec_node);

// 11_open_pipes.c
void	mini_open_pipes(t_mini *mini);

// 12_mini_execve.c
void	mini_execve(t_mini *mini);
void	mini_execve_child(t_mini *mini, t_cmd *cmd_exec_node);
void	mini_manage_execve_fd(t_cmd *cmd_exec_node);
void	mini_exit_if_fd_neg(t_cmd *cmd_exec_node);
void	mini_close_all_fd(t_mini *mini);
void	mini_close_node_fd(t_cmd *cmd_exec_node);
void 	mini_close_pipe_node_fd(t_cmd *cmd_exec_node);
void   	mini_wait_childs(t_mini *mini);
void	command_not_found_handler(t_mini *mini, t_cmd *cmd_exec_node);
void	get_captalized_errors(t_mini *mini, t_cmd *cmd_exec_node);

// 96_builtin_pwd.c
int	mini_pwd(t_token *arg, t_dict **env_list);

// 97_builtin_unset.c
int	mini_unset(t_token *arg, t_dict **env_list);

// 97_utils_1.c
int	mini_valid_identifier(char *str, t_dict **env_list, int start, int state);

// 98_builtin_export.c
int	mini_export(t_token *arg, t_dict **env_list);

// 98_utils_1.c
int	mini_env_identifier(char *str, t_dict **env_list, int start, int state);
int	mini_env_get_next_state(int state, int column);
int	mini_env_get_column(char c);

// 99_builtin_echo.c
int		mini_echo(t_token *arg);
int		mini_add_new_line(char *str);

#endif
