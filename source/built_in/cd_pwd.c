#include "../../include/built_in.h"

int	exec_pwd(t_context *ctx)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		set_var("PIPESTATUS", GENERAL_ERROR);
		return (error_new_int("pwd", "getcwd", strerror(errno), ctx->fd[2]));
	}
	ft_putstr_fd(path, ctx->fd[1]);
	ft_putstr_fd("\n", ctx->fd[1]);
	free(path);
	return (0);
}

int	change_dir_var(t_pair_lst *lst, char *var_name, int fd_err)
{
	t_pair_lst	*env_var;
	char		*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		set_var("PIPESTATUS", GENERAL_ERROR);
		return (error_new_int("cd", "getcwd", strerror(errno), fd_err));
	}
	env_var = find_env_var(lst, var_name);
	if (!env_var)
		set_var(var_name, path);
	else
	{
		free(env_var->value);
		env_var->value = ft_strdup(path);
		free(path);
		if (!env_var->value)
		{
			set_var("PIPESTATUS", GENERAL_ERROR);
			return (error_new_int("cd", "ft_stdrup", "Malloc failed\n", fd_err));
		}
	}
	return (0);
}

static	int	just_cd_command(t_pair_lst	*env_var, t_context *ctx)
{
	env_var = find_env_var(g_env.env_vars, "HOME");
	if (!env_var)
	{
		set_var("PIPESTATUS", GENERAL_ERROR);
		return (error_new_int("cd", "HOME", "not set", ctx->fd[2]));
	}
	if (chdir(env_var->value) == -1)
	{
		set_var("PIPESTATUS", GENERAL_ERROR);
		error_new_int("cd", env_var->value, strerror(errno), ctx->fd[2]);
		return (1);
	}
	return (change_dir_var(g_env.env_vars, "PWD", ctx->fd[2]));
}

int	exec_cd(char **arguments, t_context *ctx)
{
	t_pair_lst	*env_var;
	char		*tmp;

	tmp = NULL;
	if (arguments[1] && ft_strncmp(arguments[1], "-", 2) == 0)
	{
		env_var = find_env_var(g_env.env_vars, "OLDPWD");
		if (env_var)
			tmp = ft_strdup(env_var->value);
	}
	change_dir_var(g_env.env_vars, "OLDPWD", ctx->fd[2]);
	if (!arguments[1])
		return (just_cd_command(env_var, ctx));
	if (ft_strncmp(arguments[1], "-", 2) != 0)
		tmp = ft_strdup(arguments[1]);
	if (chdir(tmp) == -1)
	{
		set_var("PIPESTATUS", GENERAL_ERROR);
		error_new_int("cd", tmp, strerror(errno), ctx->fd[2]);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (change_dir_var(g_env.env_vars, "PWD", ctx->fd[2]));
}
