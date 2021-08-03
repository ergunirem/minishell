/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_reassign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/02 16:12:12 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/02 16:13:02 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Take two pointers as parameters.
** Frees the first. Returns the second.
**
** Used to reassign allocated pointers without creating leaks.
**
**	Example :
**
** oldstr = ft_reassign (oldstr, newstr);
*/
void	*ft_reassign(void *old_ptr, void *new_ptr)
{
	free(old_ptr);
	return (new_ptr);
}
