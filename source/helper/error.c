#include "../../include/minishell.h"

bool	error_msg(char *msg)
{
	ft_putstr_fd("Minishell: ", 0);
	ft_putstr_fd(msg, 0);
	return (false);
}

bool	error_new_bool(char *command, char *arg, char *msg, int fd)
{
	ft_putstr_fd("Minishell: ", fd);
	ft_putstr_fd(command, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (false);
}

int		error_new_int(char *command, char *arg, char *msg, int fd)
{
	ft_putstr_fd("Minishell: ", fd);
	ft_putstr_fd(command, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (1);
}
