#include "minishell.h"

bool	error_msg(char *msg)
{
	ft_putstr_fd("Minishell: ", 0);
	ft_putstr_fd(msg, 0);
	return (false);
}
