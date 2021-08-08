#include "../../include/environment.h"

t_pair_lst	*find_env_var(t_pair_lst *lst, char *var_name)
{
	t_pair_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(var_name) == ft_strlen(tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	set_var(char *key, char *value)
{
	t_pair_lst	*new;

	new = find_env_var(g_env.env_vars, key);
	if (new)
		update_var(key, value);
	else
	{
		new = malloc(sizeof(t_pair_lst));
		if (!new)
			return ;
		new->next = NULL;
		new->key = ft_strdup(key);
		if (!new->key)
			return ;
		new->value = ft_strdup(value);
		if (!new->value)
			return ;
		ft_listadd_back((t_token **)&(g_env.env_vars), (t_token *)new);
	}
}

void	update_var(char *key, char *value)
{
	t_pair_lst	*new;

	new = find_env_var(g_env.env_vars, key);
	free(new->value);
	new->value = ft_strdup(value);
}

void	remove_var(t_pair_lst **lst, char *key)
{
	t_pair_lst	**tail;
	t_pair_lst	*rest;
	t_pair_lst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->next->key, key, ft_strlen(key))
			== 0 && ft_strlen(key) == ft_strlen(tmp->next->key))
			break ;
		tmp = tmp->next;
	}
	tail = &tmp;
	rest = tmp->next->next;
	free((*tail)->next->key);
	free((*tail)->next->value);
	free((*tail)->next);
	(*tail)->next = rest;
}
