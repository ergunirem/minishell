/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 19:37:26 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/11 15:50:49 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

/*
**	Ignores variable names that does not exit in env vars
**	Thus, unset only existing env vars
**	Errs on invalid identifier '-': unset -u
**	Errs on variable names with assignment '=': unset x=y
**	Errs on vars if invalid variable name is given: unset var@iable
**	On multiple arguments it ignores errors and unsets valid variable names
*/
int	exec_unset(char **args, int argc, t_context *ctx)
{
	int	i;
	int	err;

	err = 0;
	if (argc == 1)
		return (0);
	i = 1;
	while (args[i])
	{
		if (!ft_isname(args[i]))
		{
			err = 1;
			set_var("PIPESTATUS", GENERAL_ERROR);
			error_new_int(args[0], args[i], ID_ERR_MSG, ctx->fd[2]);
		}
		else if (find_env_var(g_env.env_vars, args[i]))
			remove_var(&g_env.env_vars, args[i]);
		i++;
	}
	return (err);
}
