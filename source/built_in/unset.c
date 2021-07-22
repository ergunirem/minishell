#include "../../include/built_in.h"
#include "../../include/environment.h"

int	exec_unset(char **args, int argc)
{
	int	i;

	if(argc == 1)
		return (0);
	i = 1;
	while(args[i])
	{
		if (!ft_isname(args[i]))
			error_new_int(args[0], args[i], UNSET_ERR_MSG);
		else if(ft_strchr(args[i], '='))
			error_new_int(args[0], args[i], UNSET_ERR_MSG);
		else if(find_env_var(g_env.env_vars, args[i]))
			remove_var(&g_env.env_vars, args[i]);
		i++;
	}
	// if(is_in(&g_env.shell_vars, args[1]))
	// if(is_in_declare?(&g_env.env_vars, args[1]))
	//unset from shell variables, just key declaration?
	return (0);
}
