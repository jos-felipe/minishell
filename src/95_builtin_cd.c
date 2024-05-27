/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   95_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/27 15:22:21 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int	mini_cd(t_token *arg, t_dict **dict)
{
	char	*directory;
	char	*old_directory;
	
	if (!arg)
		directory = getenv("HOME");
	else
		directory = arg->token;
	return (mini_chdir_and_env_sync(*dict, directory));
}

void	mini_cd_go_home(t_dict *dict)
{
	char	*var[2];
	char	*old_path;
	
	old_path = ft_dict_get_value(dict, "PWD");
	var[0] = "PWD";
	var[1] = ft_dict_get_value(dict, "HOME");
	ft_dict_update(dict, var);
	var[0] = "OLDPWD";
	var[1] = old_path;
	ft_dict_update(dict, var);
}

int	mini_cd_sync(t_dict *dict, char *directory)
{
	int		ret;
	char	*var[2];
	
	var[0] = "OLDPWD";
	var[1] = getcwd(NULL, 0);
	ft_collect_mem_env(var[1]);
	// ft_printf("oldpwd: %s\n", var[1]);
	ret = chdir(directory);
		if (!ret)
		{
			ft_dict_update(dict, var);
			var[0] = "PWD";
			var[1] = getcwd(NULL, 0);
			ft_collect_mem_env(var[1]);
			// ft_printf("pwd: %s\n", var[1]);
			ft_dict_update(dict, var);
		}
	return (ret);
}

int	mini_chdir_and_env_sync(t_dict *dict, char *directory)
{
	int		ret;
	char	*var[2];
	
	var[0] = "OLDPWD";
	var[1] = getcwd(NULL, 0);
	ft_collect_mem_env(var[1]);
	ret = chdir(directory);
		if (!ret)
		{
			ft_dict_update(dict, var);
			var[0] = "PWD";
			var[1] = getcwd(NULL, 0);
			ft_collect_mem_env(var[1]);
			ft_dict_update(dict, var);
		}
	return (ret);
}
