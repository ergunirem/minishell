#include "../../include/built_in.h"

int	exec_pwd(t_context *ctx)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (error_new_int("pwd", "getcwd", strerror(errno), ctx->fd[2]));
	ft_putstr_fd(path, ctx->fd[1]);
	ft_putstr_fd("\n", ctx->fd[1]);
	// printf("in pwd ctx fd[0] fd[1] and close is %d %d %d\n", ctx->fd[0], ctx->fd[1], ctx->fd_close);
	free(path);
	return (0);
}

int	change_dir_var(t_pair_lst *lst, char *var_name, int fd_err)
{
	t_pair_lst	*env_var;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (error_new_int("cd", "getcwd", strerror(errno), fd_err));
	env_var = find_env_var(lst, var_name);
	free(env_var->value);
	env_var->value = ft_strdup(path);
	if (!env_var->value)
		return (error_new_int("cd", "ft_stdrup", "Malloc failed\n", fd_err));
	free(path);
	return (true);
}

int	exec_cd(char **arguments, t_context *ctx)
{
	t_pair_lst	*env_var;
	char		*tmp;

	if (arguments[1] && ft_strncmp(arguments[1], "-", 2) == 0)
	{
		env_var = find_env_var(g_env.env_vars, "OLDPWD");
		//prints out the oldpwd when cd -
		tmp = ft_strdup(env_var->value);
	}
	change_dir_var(g_env.env_vars, "OLDPWD", ctx->fd[2]);
	if (!arguments[1])
	{
		env_var = find_env_var(g_env.env_vars, "HOME");
		if (chdir(env_var->value) == -1)
			return (error_new_int("cd", env_var->value, strerror(errno), ctx->fd[2]));
		return(change_dir_var(g_env.env_vars, "PWD", ctx->fd[2]));
	}
	if (ft_strncmp(arguments[1], "-", 2) != 0)
		tmp = ft_strtrim(arguments[1], "\""); //any issue with using both " and '
	if (chdir(tmp) == -1)
		return (error_new_int("cd", tmp, strerror(errno), ctx->fd[2]));
	free(tmp);
	return (change_dir_var(g_env.env_vars, "PWD", ctx->fd[2]));
}
