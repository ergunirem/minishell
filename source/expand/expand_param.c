#include "../../include/expansion.h"
#include "../../include/minishell.h" //I need this for libft.h > what else to do?

/*
xxx$VAR
If VAR is non-existent, ignore it and save it as xxx.
Else, append it to the string, xxxVAR_VALUE. > in expanded rest
// offset = 0; //the rest? why 0 = don't change it if ignored, if not append len(var_value)
$ inside quotes " "? echo "irem $OLDPWD" > irem /Users/ergunirem ergun
inside quotes ' '? echo 'irem $OLDPWD' > irem $OLDPWD
> expansion is prevented by single quotes. echo $$$'$PWD' > 53471$PWD >
*/

char	*expanded_rest(char *arg, int sign_amount, int *offset)
{
	char		*expanded_rest;
	char		*var_name;
	t_pair_lst	*env_var;
	int			count;

	printf("IN\n");
	count = 0;
	while (arg[sign_amount + count])
	{
		//stop if char's against variable naming convention
		if (!ft_isalnum(arg[sign_amount + count]) && arg[sign_amount + count] != '_')
			break ;
		count++;
	}
	printf("Count:%d\n", count);
	var_name = ft_substr(arg, sign_amount, count);
	env_var = find_env_var(g_env.env_vars, var_name);
	free(var_name);
	if (!env_var)
	{
		if (count != 0)
			ft_memmove(arg, arg + sign_amount + count, ft_strlen(arg + sign_amount + count) + 1);
		else
			*offset = *offset + sign_amount;
		printf("MOVED:%s\n", arg);
		return (NULL);
	}
	expanded_rest = ft_strjoin(env_var->value, arg + sign_amount + count);
	*offset = *offset + ft_strlen(env_var->value);
	return (expanded_rest);
}

char	*expand_and_append(char *arg_rest, int *offset)
{
	int		i;

	i = 0;
	while (arg_rest[i])
	{
		if (arg_rest[i] == '$' && arg_rest[i + 1] == '$'
			|| arg_rest[i] == '$' && arg_rest[i + 1] == '\0')
			i++;
		else
			return (expanded_rest(arg_rest, i + 1, offset));
	}
	*offset = *offset + i; //if echo $$$$$
	return (NULL);
}

static	void	skip_single_quotes(char *arg, int *offset)
{
	char	quote;

	quote = arg[*offset];
	*offset = *offset + 1;
	while (arg[*offset] != quote && arg[*offset])
		(*offset)++;
	(*offset)++;
}

static	void	move_to_sign(char *arg, int *offset, int *double_quote_mode)
{
	// int	double_quote_mode;
	printf("In MTS: %d\n", *offset);
	// double_quote_mode = 0;
	//how to handle "' '" ? or ""irem""'$USER'
	while (arg[*offset])
	{
		if (arg[*offset] == '\"')
		{
			printf("In DQM: %d\n", *offset);
			(*double_quote_mode)++;
			printf("In DQM-N: %d\n", *double_quote_mode);
			// (*offset)++;
			printf("OFFSET: %d\n", *offset);
		}

		if (*double_quote_mode > 1)
		{
			(*offset)++;
			printf("B: %d\n", *offset);
			break ;
		}

		if(arg[*offset] == '\'' && *double_quote_mode == 0)
		{
			printf("SB\n");
			break ;
		}
		if(arg[*offset] == '$')
			break ;
		(*offset)++;
	}
	printf("LAST OFF: %d\n", *offset);
}

char	*expand_param(char *arg)
{
	char	*until_sign;
	char	*expanded_rest;
	int		offset;
	int		until;
	int		double_quote_mode;


	offset = 0;
	until = 0;
	while (arg[offset])
	{
		double_quote_mode = 0;
		if(arg[offset] == '\'')
			skip_single_quotes(arg, &offset);
		move_to_sign(arg, &offset, &double_quote_mode);
		until = offset;
		// printf("X");
		// printf("ARG: %s\n", arg + offset);
		if (arg[offset] == '$')
		{
			// printf("IN %d\n", offset);
			expanded_rest = expand_and_append(arg + offset, &offset);
			if (!expanded_rest)
				continue ;
			until_sign = ft_substr(arg, 0, until);
			free(arg);
			arg = ft_strjoin_free(until_sign, expanded_rest, 3);
			// printf("EXP: %s\n", arg);
			printf(": %d\n",offset);
			if (double_quote_mode == 1)
				offset++;;
			// offset++; //problematic part;
			// continue ;
		}
		// if (arg[offset] != '\'' && arg[offset] != '\"')
		// 	offset++;
	}
	return (arg);//return str or change it with double pointer?
}
