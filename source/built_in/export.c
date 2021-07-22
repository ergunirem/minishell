#include "../../include/built_in.h"
#include "../../include/environment.h"

/*
**	Returns error if ?.
*/

int	exec_export(char **args, int argc)
{
	int			i;
	t_pair_lst	*new;

	//keys without values? //if in shell vars move from there?
	if (argc == 1)
		return (-1); //?print_w_declare?
	i = 1;
	while(args[i])
	{
		if (ft_strrchr(args[i], '-'))
			return(error_new_int("export", args[i], "not a valid identifier\n"));
		new = create_key_value_pair(args[i]);
		if (!ft_isname(new->key))
		{
			free(new);
			return(error_new_int("export", args[i], "not a valid identifier\n"));
		}
		if (find_env_var(g_env.env_vars, new->key))
		{
			update_var(g_env.env_vars, new->key, new->value);
			free(new);
		}
		else
			ft_listadd_back((t_token **)&g_env.env_vars, (t_token *)new);
		i++;
	}
	return (0);
}
