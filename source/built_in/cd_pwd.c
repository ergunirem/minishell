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
		return (error_new_bool("cd", "ft_stdrup", "Malloc failed\n", 1));
	free(path);
	return (true);
}

bool	exec_cd(char **arguments)
{
	t_pair_lst	*env_var;
	char		*tmp;

	change_dir_var(g_env.env_vars, "OLDPWD");
	if (!arguments[1])
	{
		env_var = find_env_var(g_env.env_vars, "HOME");
		if (chdir(env_var->value) == -1)
			return (error_new_bool("cd", env_var->value, strerror(errno), 1));
		return(change_dir_var(g_env.env_vars, "PWD"));
	}
	//should we get rid of quotes in lexer part?
	tmp = ft_strtrim(arguments[1], "\""); //any issue with using both " and '
	if (chdir(tmp) == -1)
		return (error_new_bool("cd", tmp, strerror(errno), 1));
	free(tmp);
	return (change_dir_var(g_env.env_vars, "PWD"));
}
