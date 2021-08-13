/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 20:04:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/09 17:30:56 by Xiaojing      ########   odam.nl         */
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
	if (args[1])
	{
		if (!check_numeric(args[1]))
		{
			ft_putstr_fd("logout\n", ctx->fd[2]);
			error_new_int("exit", args[1], NUMERIC_ERROR, ctx->fd[2]);
			exit_code = 255;
			exit(exit_code % 256);
		}
		exit_code = ft_atoi(args[1]);
	}
	if (argc > 2)
	{
		set_var("PIPESTATUS", GENERAL_ERROR);
		ft_putstr_fd("logout\n", ctx->fd[2]);
		return (error_new_int("exit", NULL, MANY_ARG_ERR_MSG, ctx->fd[2]));
	}
	ft_putstr_fd("logout\n", ctx->fd[2]);
	exit(exit_code % 256);
}
