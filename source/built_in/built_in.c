#include "../../include/minishell.h"

bool	is_built_in(char *cmd)
{
	if(ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if(ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if(ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if(ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if(ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if(ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	if(ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

bool	exec_built_in(char **args, int argc, t_context *ctx, char **envp)
{
	if(ft_strncmp(args[0], "cd", 3) == 0)
		return(exec_cd(args));
	if(ft_strncmp(args[0], "pwd", 4) == 0)
		return(exec_pwd(ctx));
	if(ft_strncmp(args[0], "export", 7) == 0)
		return(exec_export(args, argc));
	if(ft_strncmp(args[0], "unset", 6) == 0)
		return(exec_unset(args, argc));
	if(ft_strncmp(args[0], "env", 4) == 0)
		return(exec_env(args, argc));
	if(ft_strncmp(args[0], "echo", 5) == 0)
		return(exec_echo(args, argc, ctx));
	if(ft_strncmp(args[0], "exit", 5) == 0)
		return(exec_exit(args, argc, ctx));
	return (false);
}
