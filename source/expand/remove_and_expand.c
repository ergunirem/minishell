/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_and_expand.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 20:58:19 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/28 18:05:40 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"
#include "../../include/minishell.h"

/*
**	If there is no quote in argument, q_mode is already set to zero.
**	If q_mode is zero, and there is a quote char
****		q_mode is set to the type of the qoute (quote is opened)
**	If q_mode is not zero, and qoute char is the same as q_mode
****		q_mode is set to zero again (quote is closed)
*/
static void	set_quote_mode(char c, char *q_mode)
{
	if ((c == '\'' || c == '\"') && *q_mode == 0)
		*q_mode = c;
	else if ((c == '\'' && *q_mode == '\'') || (c == '\"' && *q_mode == '\"'))
		*q_mode = 0;
}

/*
**	If arg is $, "$", $$, "$$" etc, it skips the $ char
**	Traverses until a char that's not in variable name convention
*/
static int	get_var_name(char *s, int i, int *j)
{
	if (s[i + 1] == '\0' || s[i + 1] == '$' || s[i + 1] == '\"')
		return (0);
	if (ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		(*j)++;
	if (*j == 1 && !ft_isdigit(s[i + 1]))
		return (0);
	if (*j == 2)
	{
		while (ft_isalnum(s[i + *j]) || s[i + *j] == '_')
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
static int	expand(char **str, int i, char q_mode)
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
	if (!env_var || !env_var->value)
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

/*
**	First sets the qoute mode
**	If a quote char, it removes it based on the qoute_removal rule
**	If $ char, it calls the expand function unless q_mode is single qoute
*/
char	*remove_quotes_and_expand(char *arg)
{
	char			*s;
	int				i;
	char			q;

	s = ft_strdup(arg);
	if (!s)
		return (NULL);
	q = 0;
	i = 0;
	while (s[i])
	{
		set_quote_mode(s[i], &q);
		if ((s[i] == '\"' && q != '\'') || (s[i] == '\'' && q != '\"'))
		{
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i--;
		}
		else if (s[i] == '$' && q != '\'')
			i = expand(&s, i, q) - 1;
		i++;
		if (i < 0)
			break ;
	}
	free(arg);
	return (s);
}
