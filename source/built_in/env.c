#include "../../include/built_in.h"

/*
**	Returns error if env is called with other arguments.
*/

int	exec_env(char **args, int argc)
{
	if(argc != 1)
		return (error_msg(ENV_ERR_MSG));
	while(g_env.env_vars)
	{
		ft_putstr_fd(g_env.env_vars->key, 0);
		ft_putstr_fd("=", 0);
		ft_putstr_fd(g_env.env_vars->value, 0);
		ft_putstr_fd("\n", 0);
		g_env.env_vars = g_env.env_vars->next;
	}
	return (0);
}
