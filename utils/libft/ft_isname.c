/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isname.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/22 12:34:14 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/07/22 12:56:49 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Rules for naming a variable
** A variable name can only have letters
** (both uppercase and lowercase letters), digits and underscore.
** First letter of a variable should be either a letter or an underscore.
*/

int	ft_isname(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		i = 1;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (str[i])
			return (0);
		else
			return (1);
	}
	return (0);
}
