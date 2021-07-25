#include "../../include/built_in.h"
#include "../../include/environment.h"

int	exec_unset(char **args, int argc)
{
	if(argc == 1)
		return (0);
	if(ft_strchr(args[1], '='))
		return (error_new_int(args[0], args[1], UNSET_ERR_MSG));
	if(find_env_var(g_env.env_vars, args[1]))
		remove_var(&g_env.env_vars, args[1]);
	// if(is_in(&g_env.shell_vars, args[1]))
	// if(is_in_declare?(&g_env.env_vars, args[1]))
	//unset from shell variables, just key declaration?
	return (0);
}
