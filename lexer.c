
#include "minishell.h"

// throw error with unclosed quote
//

t_token	*initialize(void)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	return (new);
}



void	lexer(char *str, t_token **token)
{
	t_token	*head;
	t_token	*new;
	t_token	*tail;
	char	*temp;
	int		n;


	head = new;
	while (*str != '\n')
	{
		n = 0;
		//initialize new token
		new = initialize();

		//check function
		if //check for special chars (| > >> etc.))

		else //everything else except special
				//check for quotes (keep the quote?)
				//check for word

		if (*str == '\'' || *str == '\"')
		{
			temp = str;
			str++;
			while (*str != '\'' || *str != '\"')
			{
				n++;
				str++;
			}
			if (*str == '\'' || *str == '\"')
				new->content = ft_substr(temp, 0, n + 1);
			else
				return ;
		}
		ft_lstadd_back((t_list **)&head, (t_list *)new);
	}
}
