
#include "minishell.h"

// throw error with unclosed quote
//

t_token	*initialize(void)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->content = NULL;
	return (new);
}

void	tokenize_special_char(char *str, t_token *new)
{
	//how to move within string so that in the lexer func it moves to the next char?
	// and how to make the function go: this token is done go to the next token?
	if (str[0] == '|'&& str[1] == ' ')
		new->type = CHAR_PIPE;
	else if (str[0] == '<' && str[1] == ' ')
		new->type = CHAR_LESS;
	else if (str[0] == '<' && str[1] == '<' && str[2] == ' ')
		new->type = CHAR_DLESS;
	else if (str[0] == '>' && str[1] == ' ')
		new->type = CHAR_GREAT;
	else if (str[0] == '>' && str[1] == '>' && str[2] == ' ')
		new->type = CHAR_DGREAT;
	else
	{
		printf("error in check_special\n");
		return; //error?
	}
}

void	lexer(char *str, t_token **token)
{
	t_token	*head;
	t_token	*new;
	t_token	*tail;
	char	*temp;
	int		n;

	head = initialize();
	head->next = new;
	while (*str != '\0')
	{
		//initialize new token
		new = initialize();

		////check for special chars (| > >> etc.))
		if (ft_strchr("|><", str[0]))
		{
			tokenize_special_char(str, new);
			return ;
		}
		else
			return ;


		//what about $ with environment vars?
		// else //everything else except special
		// 		//check for quotes (keep the quote?)
		// 		//check for word

		//ft_lstadd_back((t_list **)&head, (t_list *)new);
	}
}
