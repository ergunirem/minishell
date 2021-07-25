/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_isalnum.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/22 12:07:34 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/07/22 12:27:26 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isalnum(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isalnum((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}
