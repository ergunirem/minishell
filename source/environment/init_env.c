#include "../../include/environment.h"

t_env	g_env;

void	set_key_value_pair(char *env_var, t_pair_lst *new)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		if(env_var[i] == '=')
		{
			new->key = ft_substr(env_var, 0, i);
			new->value = ft_substr(env_var, i + 1, ft_strlen(env_var));
			break;
		}
		i++;
	}
	// printf("key:%s value:%s\n", new->key, new->value);
}

t_pair_lst *copy_envp(char **envp)
{
	// t_pair_lst	**env_vars;
	t_pair_lst	*new;

	g_env.env_vars = NULL;
	new = malloc(sizeof(t_pair_lst));
	if (!new)
		return (NULL); //error malloc
	new->next = NULL;
	new->key = NULL;
	new->value = NULL;
	while (*envp)
	{
		set_key_value_pair(*envp, new);
		// printf("%s\n", *envp);
		envp++;
		ft_listadd_back((t_token **)&(g_env.env_vars), (t_token *)new);
		printf("key:%s value:%s\n", (g_env.env_vars)->key, (g_env.env_vars)->value);
	}

	// while(*env_vars)
	// {
	// 	printf("key:%s value:%s\n", (*env_vars)->key, (*env_vars)->value);
	// 	*env_vars = (*env_vars)->next;
	// }
	return (g_env.env_vars);
}

int	init_env_vars(char **envp)
{
	t_pair_lst *env_vars;
	// g_env.env_vars = copy_envp(envp);
	copy_envp(envp);
	printf("key:%s value:%s\n", g_env.env_vars->key, g_env.env_vars->value);
	env_vars = g_env.env_vars;

	// int i = 0;
	// while(env_vars)
	// {
	// 	i++;
	// 	printf("%d) key:%s value:%s\n", i, env_vars->key, env_vars->value);
	// 	env_vars = env_vars->next;
	// }
	return (0);
}
