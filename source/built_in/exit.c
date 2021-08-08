/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 20:04:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/08 16:42:02 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

int	check_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	exec_exit(char **args, int argc, t_context *ctx)
{
	int	exit_code;

	exit_code = 0;
	if (argc > 2)
	{
		update_var("PIPESTATUS", GENERAL_ERROR);
		return (error_new_int("exit", NULL, MANY_ARG_ERR_MSG, ctx->fd[2]));
	}
	if (args[1])
	{
		if (!check_numeric(args[1]))
		{
			error_new_int("exit", args[1], NUMERIC_ERROR, ctx->fd[2]);
			exit_code = 2;
			exit(exit_code % 256);
		}
		if (exit_code != 2)
			exit_code = ft_atoi(args[1]);
	}
	ft_putstr_fd("exit\n", ctx->fd[2]);
	exit(exit_code % 256);
}
