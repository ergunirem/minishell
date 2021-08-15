/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:00:38 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:00:40 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_set(char **argv, t_context *ctx, int count, int n)
{
	if (!argv)
		free_array(argv);
	close_redirection(ctx->redir, count);
	if (!ctx->redir)
		free(ctx->redir);
	return (n);
}
