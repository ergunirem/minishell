/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 20:04:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 21:15:05 by icikrikc      ########   odam.nl         */
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

int	handle_non_numeric(char **args, int *exit_code, t_context *ctx)
{
	if (g_env.pipe_exit == 0)
		ft_putstr_fd("exit\n", ctx->fd[2]);
	error_new_int("exit", args[1], NUMERIC_ERROR, ctx->fd[2]);
	*exit_code = 255;
	if (g_env.pipe_exit == 1)
	{
		if (fork() == 0)
			exit(*exit_code % 256);
		wait(NULL);
		set_var("PIPESTATUS", "255");
		return (0);
	}
	else
		exit(*exit_code % 256);
}

int	too_many_arg(t_context *ctx)
{
	set_var("PIPESTATUS", GENERAL_ERROR);
	if (g_env.pipe_exit == 0)
		ft_putstr_fd("exit\n", ctx->fd[2]);
	error_new_int("exit", NULL, MANY_ARG_ERR_MSG, ctx->fd[2]);
	return (0);
}

int	exec_exit(char **args, int argc, t_context *ctx)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (!check_numeric(args[1]))
			return (handle_non_numeric(args, &exit_code, ctx));
		exit_code = ft_atoi(args[1]);
	}
	if (argc > 2)
		return (too_many_arg(ctx));
	if (g_env.pipe_exit == 0)
		ft_putstr_fd("exit\n", ctx->fd[2]);
	if (g_env.pipe_exit == 1)
	{
		if (fork() == 0)
			exit(exit_code % 256);
		wait (NULL);
		set_var("PIPESTATUS", ft_itoa(exit_code % 256));
	}
	else
		exit(exit_code % 256);
	return (0);
}
