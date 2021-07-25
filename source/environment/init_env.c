#include "../../include/environment.h"

t_pair_lst	*create_key_value_pair(char *env_var)
{
	int i;
	t_pair_lst *new;

	new = malloc(sizeof(t_pair_lst));
	if (!new)
		return (NULL); //error malloc
	new->next = NULL;
	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
		{
			new->key = ft_substr(env_var, 0, i);
			new->value = ft_substr(env_var, i + 1, ft_strlen(env_var));
			break;
		}
		i++;
	}
	return (new);
}

void	clone_variables(char **envp, t_pair_lst **lst)
{
	t_pair_lst *new;

	while (*envp)
	{
		new = create_key_value_pair(*envp);
		ft_listadd_back((t_token **)lst, (t_token *)new);
		envp++;
	}
}

int	init_variables(char **envp)
{
	clone_variables(envp, &(g_env.env_vars));
	// clone_variables(envp, g_env.shell_vars); //should this be created everytime there is a child process?
	return (0);
}
