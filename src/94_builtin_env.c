/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   94_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/28 11:44:28 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

// static int	mini_chdir_and_env_sync(t_dict *dict, char *directory, int print);

int	mini_env(t_token *arg, t_dict **dict)
{
	/* char	*directory;
	int		print;
	
	directory = NULL;
	print = 0;
	if (!arg)
		directory = getenv("HOME");
	else
	{
		if (!ft_strncmp(arg->token, "-", ft_strlen(arg->token)))
		{
			directory = getenv("OLDPWD");
			print = 1;
		}
		else
			directory = arg->token;
	}
	return (mini_chdir_and_env_sync(*dict, directory, print)); */
	ft_printf("Hello World!");
	return (0);
}


/* static int	mini_chdir_and_env_sync(t_dict *dict, char *directory, int print)
{
	int		ret;
	char	*var[2];
	
	var[0] = "OLDPWD";
	var[1] = getcwd(NULL, 0);
	ft_collect_mem_env(var[1]);
	ret = chdir(directory);
		if (!ret)
		{
			if (print)
				ft_printf("%s\n", ft_dict_get_value(dict, "OLDPWD"));
			ft_dict_update(dict, var);
			var[0] = "PWD";
			var[1] = getcwd(NULL, 0);
			ft_collect_mem_env(var[1]);
			ft_dict_update(dict, var);
		}
	return (ret);
} */
