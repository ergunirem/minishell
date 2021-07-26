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
*/

char	*expand_and_append(char *arg_rest)
{
	char	*var_name;
	char	*expanded_rest;
	int		i;

	while(arg[i])
}

int	expand_param(char *arg)
{
	char	*until_sign;
	char	*expanded_rest;
	int		offset;

	offset = 0;
	while(arg[offset])
	{
		if(arg[offset] == '$')
		{
			expanded_rest = expand_and_append(arg + offset);
			printf("ER: %s\n", expanded_rest);
			until_sign = ft_substr(arg, 0, offset);
			printf("US: %s\n", until_sign);
			free(arg);
			arg = ft_strjoin_free(until_sign, expanded_rest, 3);
			printf("ARG: %s\n", arg);
			offset = 0;
			continue ;
		}
		offset++;
	}
	return (0);  //return str or change it with double pointer?
}
