/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 13:15:52 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/08 16:48:25 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new && *lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->next = NULL;
	}
	else if (!*lst)
	{
		*lst = new;
		new->next = NULL;
	}
}
