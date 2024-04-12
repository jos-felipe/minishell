/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:19:25 by josfelip          #+#    #+#             */
/*   Updated: 2024/04/11 16:35:42 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*mini_get_path(char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			ft_collect_mem(path);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	free_heap(t_list *lst_memory)
{
	t_list	*tmp;

	while (lst_memory)
	{
		tmp = lst_memory;
		lst_memory = lst_memory->next;
		free(tmp->content);
		free(tmp);
	}
}

void	mini_free_split(char **split)
{
	int	i;

	if (split == NULL)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*mini_whereis(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	char	*fn;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fn = ft_strjoin(tmp, cmd);
		if (access(fn, X_OK) == 0)
		{
			free(tmp);
			mini_free_split(paths);
			return (fn);
		}
		free(fn);
		free(tmp);
		i++;
	}
	mini_free_split(paths);
	return (NULL);
}

void	mini_trashman(t_list **lst_memory)
{
	t_list	*tmp;

	while (*lst_memory)
	{
		tmp = *lst_memory;
		*lst_memory = (*lst_memory)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}
