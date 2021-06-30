
#include "minishell.h"

// throw error with unclosed quote
t_token	*ft_listlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_listadd_back(t_token **lst, t_token *new)
{
	t_token *last;

	if (new && *lst)
	{
		last = ft_listlast(*lst);
		last->next = new;
		new->next = NULL;
	}
	else if (!*lst)
	{
		*lst = new;
		new->next = NULL;
	}
}

void	ft_lst_print(t_token *token)
{
	int i = 1;
	while(token)
	{
		printf("%d) content:%s and type:%d\n", i, token->content, token->type);
		i++;
		token = token->next;
	}
}

t_token	*initialize(void)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->content = NULL;
	new->type = 0;
	return (new);
}

int	tokenize_special_char(char *str, t_token *new, int *i)
{
	// how to move within string so that in the lexer func it moves to the next char?
	// and how to make the function go: this token is done go to the next token?
	//is checking for a space after special char necessary?
	if (str[*i] == '|' && str[*i + 1] == ' ') // ?
	{
		new->type = CHAR_PIPE;
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<' && str[*i + 2] == ' ')
	{
		new->type = CHAR_DLESS;
		(*i) = (*i) + 2;
	}
	else if (str[*i] == '<' && str[*i + 1] == ' ')
	{
		new->type = CHAR_LESS;
		(*i)++;
	}
	else if (str[*i] == '>' && str[*i + 1] == '>' && str[*i + 2] == ' ')
	{
		new->type = CHAR_DGREAT;
		(*i) = (*i) + 2;
	}
	else if (str[*i] == '>' && str[*i + 1] == ' ')
	{
		new->type = CHAR_GREAT;
		(*i)++;
	}
	else
	{
		//problem: always goes into this condition when end of the line
		printf("error in check_special\n");
		return (-1); //error?
	}
	printf("new added is %s and type is %d\n", new->content, new->type);
	return (0);
}

void	lexer(char *str, t_token **token)
{
	t_token	**head;
	t_token	*new;
	char	*temp;
	int		n;
	int		i;

	*head = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		//initialize new token
		new = initialize();
		//skip whitespace
		while (ft_iswhitespace(str[i]))
			i++;
		//check for special chars
		if (ft_strchr("|><", str[i]))
		{
			if(tokenize_special_char(str, new, &i) == -1)
				return ;
		}
		else
			return ;
		ft_listadd_back(head, new);
				// //what about $ with environment vars?
		// // else //everything else except special
		// // 		//check for quotes (keep the quote?)
		// // 		//check for word
	}
	token = head;
	ft_lst_print(*token);
}
