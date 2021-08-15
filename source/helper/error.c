/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:00:17 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:00:19 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	error_msg(char *msg, char *error_code)
{
	ft_putstr_fd("Minishell: ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	set_var("PIPESTATUS", error_code);
	return (false);
}

char	**error_msg_inclfree(char *msg, char **argv, int argc)
{
	free_array2(argv, argc);
	ft_putstr_fd("Minishell: ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	return (NULL);
}

bool	error_new_bool(char *command, char *arg, char *msg, int fd)
{
	ft_putstr_fd("Minishell: ", fd);
	if (command)
	{
		ft_putstr_fd(command, fd);
		ft_putstr_fd(": ", fd);
	}
	if (arg)
	{
		ft_putstr_fd(arg, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (false);
}

int	error_new_int(char *command, char *arg, char *msg, int fd)
{
	ft_putstr_fd("Minishell: ", fd);
	if (command)
	{
		ft_putstr_fd(command, fd);
		ft_putstr_fd(": ", fd);
	}
	if (arg)
	{
		ft_putstr_fd(arg, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (1);
}

bool	lexer_error(t_token *new, char *msg, char *error_code)
{
	ft_putstr_fd("Minishell: error: ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	set_var("PIPESTATUS", error_code);
	if (new)
	{
		free(new->content);
		free(new);
	}
	return (false);
}
