#include "../../include/built_in.h"
#include "../../include/minishell.h"

int	exec_pwd(t_context *ctx)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, ctx->fd[1]);
	ft_putstr_fd("\n", ctx->fd[1]);
	free(path);
	return (0);
}

bool	change_dir_var(t_pair_lst *lst, char *var_name)
{
	t_pair_lst	*env_var;
	char		*path;

	path = getcwd(NULL, 0);
	// if (!path)
		// return (error_new_bool("cd", "getcwd", strerror(errno)));
	env_var = find_env_var(lst, var_name);
	free(env_var->value);
	env_var->value = ft_strdup(path);
	if (!env_var->value)
		return (error_new_bool("cd", "ft_stdrup", "Malloc failed\n"));
	free(path);
	return (true);
}

bool	exec_cd(char **arguments)
{
	t_pair_lst	*env_var;

	change_dir_var(g_env.env_vars, "OLDPWD");
	if (!arguments[1])
	{
		env_var = find_env_var(g_env.env_vars, "HOME");
		if (chdir(env_var->value))
			return (error_msg(CD_ERROR_MSG));
	}
	else if (chdir(arguments[1]) == -1)
		return (error_msg(CD_ERROR_MSG));
	change_dir_var(g_env.env_vars, "PWD");
	return (true);
}
