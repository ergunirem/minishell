/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstfree.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 13:15:28 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/05/23 19:26:40 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstfree(t_list **ptr_lst)
{
	t_list	*temp;

	if (!ptr_lst || !*ptr_lst)
		return ;
	while (*ptr_lst)
	{
		temp = (*ptr_lst)->next;
		free(*ptr_lst);
		*ptr_lst = temp;
	}
	return ;
}

void	ft_lstfree_w_content(t_list **ptr_lst)
{
	t_list	*temp;

	if (!ptr_lst || !*ptr_lst)
		return ;
	while (*ptr_lst)
	{
		temp = (*ptr_lst)->next;
		free((*ptr_lst)->content);
		free(*ptr_lst);
		*ptr_lst = temp;
	}
	return ;
}
