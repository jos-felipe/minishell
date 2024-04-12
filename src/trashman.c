/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:44:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/04/12 10:47:29 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"

// t_list    **get_mem_address(void)
// {
//     static t_list    *ptr;

//     return (&ptr);
// }

// void    collect_mem(void *content)
// {
// 	t_list **ptr;

//     ft_lstadd_back(get_mem_address(), ft_lstnew(content));
	
// 	ptr = get_mem_address();
// }

// void    *allocate_mem(size_t nmemb, size_t size)
// {
//     void    *content;
	
//     content = ft_calloc(nmemb, size);
//     collect_mem(content);

// 	return (content);
// }

// void	mini_free_trashman(t_list **lst_memory)
// {
// 	t_list	*next;

// 	while (*lst_memory)
// 	{
// 		next = (*lst_memory)->next;
// 		free((*lst_memory)->content);
// 		free(*lst_memory);
// 		*lst_memory = next;
// 	}
// 	*lst_memory = NULL;
// }