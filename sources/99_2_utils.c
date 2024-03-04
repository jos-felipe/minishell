/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_2_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:00:39 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/22 19:38:38 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_int_overflow(long nbr)
{
	return (nbr > INT_MAX || nbr < INT_MIN);
}

int	only_digit(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	push_count_words(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++word_count;
		while (*s && *s != sep)
			++s;
	}
	return (word_count);
}

void	push_free_split(char **split)
{
	int	i;

	if (ft_strncmp("placeholder", split[0], 11) == 0)
	{
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	push_error(t_bst **head)
{
	ft_putstr_fd("Error\n", 2);
	bst_free_all(*head);
	exit(1);
}
