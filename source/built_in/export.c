#include "../../include/built_in.h"

/*
**	Returns error if env is called with other arguments.
*/

void	print_x(t_pair_lst *env_vars)
{
	int i = 0;
	while(env_vars)
	{
		i++;
		printf("%d) key:%s value:%s\n", i, env_vars->key, env_vars->value);
		env_vars = env_vars->next;
	}
}

int	exec_export(char **args, int argc)
{
	t_pair_lst *new;
	int	i;

	printf("EXPORT\n");
	//error check for options
	//keys without values?
	// if (argc == 1)
	//if in shell vars move from there?
	//there can be multiple assignments!
	//dont add if duplicate?
	i = 1;
	//only updates the list within function scope but it's a global variable?
	while(args[i])
	{
		new = create_key_value_pair(args[i]);
		// printf("%d) key:%s value:%s\n", i, new->key, new->value);
		ft_listadd_back((t_token **)&(g_env.env_vars), (t_token *)new);
		i++;
	}
	print_x(g_env.env_vars);
	return (0);
}
