/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 19:21:18 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 16:30:08 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

/*
**	Returns error if env is called with other arguments.
*/
int	exec_env(char **args, int argc, t_context *ctx)
{
	t_pair_lst	*env_lst;

	if (argc != 1)
	{
		set_var("PIPESTATUS", ENV_ERROR);
		error_new_int("env", "", MANY_ARG_ERR_MSG, ctx->fd[2]);
		return (0);
	}
	env_lst = g_env.env_vars;
	while (env_lst)
	{
		ft_putstr_fd(env_lst->key, ctx->fd[1]);
		ft_putstr_fd("=", ctx->fd[1]);
		ft_putstr_fd(env_lst->value, ctx->fd[1]);
		ft_putstr_fd("\n", ctx->fd[1]);
		env_lst = env_lst->next;
	}
	return (0);
}
