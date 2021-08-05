#include "../../include/minishell.h"

bool	error_msg(char *msg, char *error_code)
{
	ft_putstr_fd("Minishell: ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	update_var("PIPESTATUS", error_code);
	return (false);
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

int		error_new_int(char *command, char *arg, char *msg, int fd)
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
	return (1); //will it be -1 when incorporated into get_path error message
}

bool	lexer_error(t_token *new, char *msg, char *error_code)
{
	ft_putstr_fd("Minishell: error: ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	update_var("PIPESTATUS", error_code);
	if (new)
	{
		free(new->content);
		free(new);
	}
	return (false);
}
