/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_remake_environ.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:42:16 by gfantoni          #+#    #+#             */
/*   Updated: 2024/05/24 19:51:26 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	mini_get_env_list_size(t_dict *env_list);
static int	mini_get_env_line_size(char *var, char *value);

void	mini_remake_environ(t_mini *mini)
{
	t_dict	*env_list;
	char	**mini_environ;
	char	*key_plus_equal;
	char	*mini_environ_curr;
	int		env_size;
	int		var_size;
	int		i;

	env_list = mini->env_list;
	env_size = mini_get_env_list_size(env_list);
	mini_environ = (char **)ft_calloc(sizeof(char *), env_size + 1);
	ft_collect_mem(mini_environ);
	i = 0;
	while (env_list)
	{
		var_size = mini_get_env_line_size(env_list->key, env_list->value);
		key_plus_equal = ft_strjoin(env_list->key, "=");
		ft_collect_mem(key_plus_equal);
		mini_environ_curr = ft_strjoin(key_plus_equal, env_list->value);
		ft_collect_mem(mini_environ_curr);
		mini_environ[i] = mini_environ_curr;
		env_list = env_list->next;
		i++;
	}
	mini->mini_environ = mini_environ;
}

static int	mini_get_env_list_size(t_dict *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}

static int	mini_get_env_line_size(char *var, char *value)
{
	int	var_size;
	int	value_size;

	var_size = ft_strlen(var);
	value_size = ft_strlen(value);
	return (var_size + value_size + 1);
}
