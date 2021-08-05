/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 09:19:07 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/05 09:19:11 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	returns false if
**		There is nothing before a '|'
**		There is nothing after a '|'
*/
static	bool	check_pipe(t_token *tokens)
{
	if (tokens->type == CHAR_PIPE)
		return (false);
	while (tokens)
	{
		if (tokens->type == CHAR_PIPE)
		{
			if (!tokens->next)
				return (false);
			else if (tokens->next->type == CHAR_PIPE)
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

/*
**	returns false if
**		There is nothing after a '>' '<' '>>' '<<'
*/
static	bool	check_redirection(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == CHAR_LESS || tokens->type == CHAR_DLESS
			|| tokens->type == CHAR_GREAT || tokens->type == CHAR_DGREAT)
		{
			if (!tokens->next)
				return (false);
			else if (tokens->next->type != CHAR_WORD)
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

/*
**	returns false if
**		the token list is empty to prevent calling parser function
**		pipe check fails
**		redirection check fails
*/
bool	check_list(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (!check_pipe(tokens))
		return (error_msg(PIPE_ERROR_MSG, SYNTAX_ERROR));
	if (!check_redirection(tokens))
		return (error_msg(REDIR_ERROR_MSG, SYNTAX_ERROR));
	return (true);
}
