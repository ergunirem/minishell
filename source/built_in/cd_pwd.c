#include "../../include/built_in.h"

int	exec_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		error_new("pwd", "getcwd", strerror(errno));
		return (1);
	}
	ft_putstr_fd(path, 0);
	ft_putstr_fd("\n", 0);
	free(path);
	return (0);
}

bool	change_dir_var(char *var_name)
{
	t_pair_lst	*env_var;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (error_new("cd", "getcwd", strerror(errno)));
	env_var = find_env_var(var_name);
	free(env_var->value);
	env_var->value = ft_strdup(path);
	if (!env_var->value)
		return (error_new("cd", "ft_stdrup", "Malloc failed\n"));
	free(path);
	return (true);
}

bool	exec_cd(char **arguments)
{
	change_dir_var("OLDPWD");
	if (chdir(arguments[1]) == -1)
		return (error_msg(CD_ERROR_MSG));
	change_dir_var("PWD");
	return (true);
}
