/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/15 10:59:06 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unit_print_array_list(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->commands[i])
	{
		debug_print_parse_list(&mini->commands[i]);
		printf("\n");	
		i++;
	}
}
void	mini_init(t_mini *mini)
{

	mini->path = NULL;
	mini->lst_memory = NULL;
	mini->cmd_line = NULL;
	mini->pathname = NULL;
	mini->token_list = NULL;
	mini->commands = NULL;
	mini->syntax_error = 0;
}
int		unit_echo(t_token *arg)
{
	int	new_line;

	new_line = 1;
	if (arg && arg->token)
	{
		if (!ft_strncmp(arg->token, "-n", ft_strlen(arg->token)))
		{
			new_line = 0;
			arg = arg->next;
		}
	}
	while (arg)
	{
		ft_printf("%s", arg->token);
		arg = arg->next;
		if (arg)
			ft_printf(" ");
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}

void	unit_cmd_selection(t_token *token_lst, t_mini *mini)
{
	char	*cmd;
	t_token	*arg;

	cmd = token_lst->token;
	arg = token_lst->next;
	if (!ft_strncmp(cmd, "export", 6))
		mini->status = mini_export(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "echo", 4))
		mini->status = unit_echo(arg);
}

void	unit_cmd_router(t_mini *mini)
{
	int i;

	i = -1;
	while (mini->commands[++i])
		unit_cmd_selection(mini->commands[i], mini);
}

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;
	t_token *arg;
	int		i;

	mini.env_list = NULL;
	mini.status = 0;
	mini_getenv(&mini);
	i = 0;
	while (++i < argc)
	{
		mini_init(&mini);
		mini.cmd_line = argv[i];
		mini_tokenizer(&mini);
		mini_parser(&mini);
		mini_expansion(&mini);
		unit_cmd_router(&mini);
	}
	ft_free_trashman(ft_get_mem_address());
	return (mini.status);
}
