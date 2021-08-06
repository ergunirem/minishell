/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   peek.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 11:58:46 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/06 11:58:49 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	peak_ahead(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == CHAR_PIPE)
			return (2);
		tokens = tokens->next;
	}
	return (1);
}
