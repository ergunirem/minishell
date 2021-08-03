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
for single quotes standalone  '$PWD' + just put an if statement  in exec in expand param
remove quotes
echo ""include""
echo "'include'"
echo '"include"'
echo '''include'''''
echo "$PWD   '$PWD'"  > confused!
*/

char	*expanded_rest(char *arg, int sign_amount, int *offset)
{
	char		*expanded_rest;
	char		*var_name;
	t_pair_lst	*env_var;
	int			count;

	// printf("IN\n");
	count = 0;
	while (arg[sign_amount + count])
	{
		//stop if char's against variable naming convention
		if (!ft_isalnum(arg[sign_amount + count]) && arg[sign_amount + count] != '_')
			break ;
		count++;
	}
	// printf("Count:%d\n", count);
	var_name = ft_substr(arg, sign_amount, count);
	env_var = find_env_var(g_env.env_vars, var_name);
	free(var_name);
	if (!env_var)
	{
		if (count != 0)
			ft_memmove(arg, arg + sign_amount + count, ft_strlen(arg + sign_amount + count) + 1);
		else
			*offset = *offset + sign_amount;
		// printf("MOVED:%s\n", arg);
		return (NULL);
	}
	///safkldj dhgjkdfhgj;j;k dfsjk'dsgjfghjkghjkghjghg
	expanded_rest = ft_strjoin(env_var->value, arg + sign_amount + count);
	*offset = *offset + ft_strlen(env_var->value);
	return (expanded_rest);
}

char	*expand_and_append(char *arg_rest, int *offset)
{
	int		i;

	i = 0;
	// printf("INx\n");
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

char	*expand_param(char *arg)
{
	char	*until_sign;
	char	*expanded_rest;
	int		offset;
	int		until;

	offset = 0;
	while (arg[offset])
	{
		until = offset;
		if (arg[offset] == '$')
		{
			expanded_rest = expand_and_append(arg + offset, &offset);
			if (!expanded_rest)
				continue ;
			until_sign = ft_substr(arg, 0, until);
			free(arg);
			arg = ft_strjoin_free(until_sign, expanded_rest, 3);
			continue ;
		}
		offset++;
	}
	return (arg);//return str or change it with double pointer?
}
