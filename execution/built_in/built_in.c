#include "built_in.h"

bool	is_built_in(char *cmd)
{
	if(ft_strncmp(cmd, "cd", 3))
		return (true);
	if(ft_strncmp(cmd, "pwd", 4))
		return (true);
	if(ft_strncmp(cmd, "echo", 5))
		return (true);
	if(ft_strncmp(cmd, "export", 7))
		return (true);
	if(ft_strncmp(cmd, "unset", 6))
		return (true);
	if(ft_strncmp(cmd, "env", 4))
		return (true);
	if(ft_strncmp(cmd, "exit", 5))
		return (true);
	return (false);
}

bool	exec_built_in(char **args, int argc)
{
	if(ft_strncmp(args[0], "cd", 3))
		return(exec_cd(args));
	if(ft_strncmp(args[0], "pwd", 4))
		return(exec_pwd());
	// if(ft_strncmp(cmd, "echo", 5))
	// 	return(exec_echo());
	// if(ft_strncmp(cmd, "export", 7))
	// 	return(exec_export());
	// if(ft_strncmp(cmd, "unset", 6))
	// 	return(exec_unset());
	if(ft_strncmp(args[0], "env", 4))
		return(exec_env(args, argc));
	// if(ft_strncmp(cmd, "exit", 5))
	// 	return(exec_exit());
	return (false);
}
