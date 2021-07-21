#include "../../include/built_in.h"
#include "../../include/environment.h"

/*
**	Returns error if env is called with other arguments.
*/

int	exec_env(char **args, int argc)
{
	t_pair_lst *env_lst;

	if(argc != 1)
		return (error_msg(ENV_ERR_MSG));
	env_lst = g_env.env_vars;
	while(env_lst)
	{
		ft_putstr_fd(env_lst->key, 0);
		ft_putstr_fd("=", 0);
		ft_putstr_fd(env_lst->value, 0);
		ft_putstr_fd("\n", 0);
		env_lst = env_lst->next;
	}
	return (0);
}
