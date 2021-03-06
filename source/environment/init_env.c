/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:01:08 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:01:10 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/environment.h"

t_pair_lst	*create_key_value_pair(char *env_var)
{
	int			i;
	t_pair_lst	*new;

	new = malloc(sizeof(t_pair_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
		{
			new->key = ft_substr(env_var, 0, i);
			if (!new->key)
				return (NULL);
			new->value = ft_substr(env_var, i + 1, ft_strlen(env_var));
			if (!new->value)
				return (NULL);
			break ;
		}
		i++;
	}
	return (new);
}

int	add_env(char *envp)
{
	t_pair_lst	*new;

	new = create_key_value_pair(envp);
	if (!new)
		return (1);
	ft_listadd_back((t_token **)&(g_env.env_vars), (t_token *)new);
	return (0);
}

int	init_env_variables(char **envp)
{
	t_pair_lst	*new;

	g_env.is_forked = 0;
	g_env.pipe_exit = 0;
	while (*envp)
	{
		if (add_env(*envp) == 1)
			return (1);
		envp++;
	}
	if (add_env("PIPESTATUS=0") == 1)
		return (1);
	return (0);
}
