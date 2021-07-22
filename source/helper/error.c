#include "../../include/minishell.h"

bool	error_msg(char *msg)
{
	ft_putstr_fd("Minishell: ", 0);
	ft_putstr_fd(msg, 0);
	return (false);
}

bool	error_new_bool(char *command, char *arg, char *msg)
{
	ft_putstr_fd("Minishell: ", 0);
	ft_putstr_fd(command, 0);
	ft_putstr_fd(": ", 0);
	ft_putstr_fd(arg, 0);
	ft_putstr_fd(": ", 0);
	ft_putstr_fd(msg, 0);
	return (false);
}

int		error_new_int(char *command, char *arg, char *msg)
{
	ft_putstr_fd("Minishell: ", 0);
	ft_putstr_fd(command, 0);
	ft_putstr_fd(": ", 0);
	ft_putstr_fd(arg, 0);
	ft_putstr_fd(": ", 0);
	ft_putstr_fd(msg, 0);
	return (1);
}
