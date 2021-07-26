#include "../../include/built_in.h"

int	declare_env(t_context *ctx)
{
	t_pair_lst	*env_lst;

	env_lst = g_env.env_vars;
	while (env_lst)
	{
		ft_putstr_fd("declare -x ", ctx->fd[1]);
		ft_putstr_fd(env_lst->key, ctx->fd[1]);
		ft_putstr_fd("=\"", ctx->fd[1]);
		ft_putstr_fd(env_lst->value, ctx->fd[1]);
		ft_putstr_fd("\"\n", ctx->fd[1]);
		env_lst = env_lst->next;
	}
	return (0);
}

int	create_or_update_env(char *arg, int fd_err)
{
	t_pair_lst	*new;

	new = create_key_value_pair(arg);
	if (!ft_isname(new->key))
	{
		free_var(new);
		return (error_new_int("export", arg, "not a valid identifier\n", fd_err));
	}
	if (find_env_var(g_env.env_vars, new->key))
	{
		update_var(g_env.env_vars, new->key, new->value);
		free_var(new);
	}
	else
		ft_listadd_back((t_token **)&g_env.env_vars, (t_token *)new);
	return (0);
}

/*
**	Ignores vars without assignments: export x y=z
**	Thus, export without argument only declares env variables
**	Errs on invalid identifier '-': export -x, export xyz-xyz
**	Ignores vars if invalid variable name is given: export var@iable=x x=y
*/

int	exec_export(char **args, int argc, t_context *ctx)
{
	int			i;

	if (argc == 1)
		return (declare_env(ctx)); //I did not sort?
	i = 1;
	while (args[i])
	{
		if (ft_strrchr(args[i], '-'))
			return (error_new_int("export", args[i], IDENTIFIER_ERR_MSG, ctx->fd[2]));
		if (!ft_strrchr(args[i], '='))
		{
			i++;
			continue ;
		}
		create_or_update_env(args[i], ctx->fd[2]); //check if fails? no it goes on actually?
		i++;
	}
	return (0);
}
