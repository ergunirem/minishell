#include "../../include/expansion.h"
#include "../../include/minishell.h" //I need this for libft.h > what else to do?

/*

xxx$VAR
If VAR is non-existent, ignore it and save it as xxx.
Else, append it to the string, xxxVAR_VALUE.

$ inside quotes " "? echo "irem $OLDPWD" > irem /Users/ergunirem ergun
inside quotes ' '? echo 'irem $OLDPWD' > irem $OLDPWD

remove quotes
echo ""include""
echo "'include'"
echo '"include"'
echo '''include'''''

what about echo $$$$$$$$PWD
bash > prints out a strange number
some peer > $$$$$$$/Users/ergunirem/Desktop
echo xyz$$$PWD$XYZ$HOME > vars that don't have a value are ignored!
expansion is prevented by single quotes. echo $$$'$PWD' > 53471$PWD


trials: "iremererrt$$$PWDsfdfd"
		"iremererrt$$$PWD"

echo $XYZPWD > should print nothing!
echo $XYZPWD$HOME > print home ignore xyzpwd
*/

char	*expanded_rest(char *arg, int *offset)
{
	char		*expanded_rest;
	char		*var_name;
	t_pair_lst	*env_var;
	int			count;

	count = 0;
	while (arg[count])
	{
		if (arg[count] == '$' || arg[count] == '\"')
			break ;
		count++;
	}
	// *offset = *offset + count + 1; //messsed up!
	// printf("Count:%d\n", count);
	// printf("ARG:%s\n", arg);
	var_name = ft_substr(arg, 0, count);
	// printf("NAME:%s\n", var_name);
	env_var = find_env_var(g_env.env_vars, var_name);
	free(var_name);
	if(!env_var)
		return(NULL);
	// printf("VAR:%s\n", env_var->value);
	expanded_rest = ft_strjoin(env_var->value, arg + count);
	// printf("EXP:%s\n", expanded_rest);
	return (expanded_rest);
}

char	*expand_and_append(char *arg_rest, int *offset)
{
	int		i;

	i = 0;
	while(arg_rest[i])
	{
		if(arg_rest[i] == '$' && arg_rest[i + 1] == '$'
			|| arg_rest[i] == '$' && arg_rest[i + 1] == '\0')
			i++;
		else
			return (expanded_rest(arg_rest + i + 1, offset));
	}
	return (NULL);
}

char	*expand_param(char *arg)
{
	char	*until_sign;
	char	*expanded_rest;
	int		offset;

	offset = 0;
	while(arg[offset])
	{
		if(arg[offset] == '$')
		{
			// printf("IN-EX\n");
			expanded_rest = expand_and_append(arg + offset, &offset);
			// printf("OFFSET:%d\n", offset);
			if (!expanded_rest)
			{
				//free that arg or escape???
				//memmove if var_name is non-existent!
				// printf("NULLL\n");
				// printf("OFFSET:%d\n", offset);
				// continue ;
				break ;
			}

			// printf("ER: %s\n", expanded_rest);
			until_sign = ft_substr(arg, 0, offset);
			// printf("US: %s\n", until_sign);
			free(arg);
			arg = ft_strjoin_free(until_sign, expanded_rest, 3);
			// printf("ARG: %s\n", arg);
			//what will happen if $$$/User/ergunirem$$$$PWD? > $$$ in the beginning will be a problem!
			offset = 0;
			continue ;
		}
		offset++;
	}
	// printf("ARG: %s\n", arg);
	return (arg);  //return str or change it with double pointer?
}
