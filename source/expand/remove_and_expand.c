#include "../../include/expansion.h"
#include "../../include/minishell.h"
/* I need this for libft.h > what else to do? */

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
**	Example: $VAR.txt
**	Traverses until a char that's not in variable name convention
**	Finds the value of var in env variables
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
	//but 1TEST is no var name compliant?
	while (ft_isalnum((int)(*str)[i + j]) || (*str)[i + j] == '_')
		j++;
	// if (j == 1 && ft_index("?'\"", (*str)[i + j]) == -1)
	// 	return (i + 1);
	// if ((*str)[i + 1] == '?' && ++j)
	// 	varname = ft_strdup("PIPESTATUS");
	// else
	var_name = ft_substr(*str, i + 1, j - 1);
	env_var = find_env_var(g_env.env_vars, var_name);
	free(var_name);
	if (!env_var)
	{
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

/* //error handling with mallocs? */
char	*remove_quotes_and_expand(char *arg)
{
	char			*str;
	int				offset;
	char			q_mode;

	q_mode = 0;
	offset = 0;
	str = ft_strdup(str);
	while (str[offset])
	{
		set_quote_mode(str[offset], &q_mode);
		if ((str[offset] == '\"' && q_mode != '\'')
			|| (str[offset] == '\'' && q_mode != '\"'))
		{
			ft_memmove(&str[offset], &str[offset + 1], ft_strlen(str) - offset);
			offset--;
		}
		else if (str[offset] == '$' && q_mode != '\'')
			offset = expand(&str, offset) - 1;
		offset++;
	}
	free(arg);
	return (str);
}
