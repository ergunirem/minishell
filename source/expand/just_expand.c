/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   just_expand.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 20:58:12 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/05 20:59:50 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"
#include "../../include/minishell.h"

/*
**	If arg is $, "$", $$, "$$" etc, it skips the $ char
**	Traverses until a char that's not in variable name convention
*/
static int	get_var_name(char *str, int i, int *j)
{
	if (str[i + 1] == '\0' || str[i + 1] == '$' || str[i + 1] == '\"')
		return (0);
	if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
		(*j)++;
	if (*j == 1 && !ft_isdigit(str[i + 1]))
		return (0);
	if (*j == 2)
	{
		while (ft_isalnum(str[i + *j]) || str[i + *j] == '_')
		{
			(*j)++;
		}
	}
	return (1);
}

/*
**	Example: $VAR.txt
**	Finds the value of VAR in env variables
**	If VAR is non-existent, removes it from string
**	Else, appends the value to the string
*/
static int	expand(char **str, int i)
{
	char		*expanded;
	t_pair_lst	*env_var;
	char		*var_name;
	int			j;

	j = 1;
	if (!get_var_name(*str, i, &j) && (*str)[i + 1] != '?')
		return (i + 1);
	if ((*str)[i + 1] == '?' && ++j)
		var_name = ft_strdup("PIPESTATUS");
	else
		var_name = ft_substr(*str, i + 1, j - 1);
	env_var = find_env_var(g_env.env_vars, var_name);
	free(var_name);
	if (!env_var)
	{
		if (j == 1)
			j++;
		ft_memmove(&(*str)[i], &(*str)[i + j], ft_strlen(&(*str)[i + j]) + 1);
		return (i);
	}
	expanded = ft_strjoin_free(ft_substr(*str, 0, i), env_var->value, 1);
	expanded = ft_strjoin_free(expanded, &(*str)[i + j], 1);
	*str = ft_reassign(*str, expanded);
	return (i + ft_strlen(env_var->value) - 1);
}

char	*just_expand(char *arg)
{
	char			*str;
	int				offset;

	str = ft_strdup(arg);
	if (!str)
		return (NULL);
	offset = 0;
	while (str[offset])
	{
		if (str[offset] == '$')
			offset = expand(&str, offset) - 1;
		offset++;
	}
	free(arg);
	return (str);
}
