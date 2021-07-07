
#include "minishell.h"

// throw error with unclosed quote
//

t_token	*initialize(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->content = NULL;
	new->type = 0;
	return (new);
}

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
	t_token	*last;

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

void	tokenize_word(char *str, t_token *new, int *i)
{
	int	start;
	int	n;

	start = *i;
	n = 0;
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		n++;
		(*i)++;
	}
	new->content = ft_substr(str, start, n);
	new->type = CHAR_WORD;
	if (str[*i] != '\0')
		*i = *i + 1;
}

int	tokenize_quote_word(char *str, t_token *new, int *i)
{
	char	c;
	int		start;

	c = str[*i];
	start = *i;
	*i = *i + 1;
	while (str[*i] != c && str[*i] != '\0')
		(*i)++;
	if (str[*i] == c)
	{
		if (str[*i + 1] != '\0' && str[*i + 1] != ' ')
		{
			tokenize_word(str, new, &start);
			*i = start;
		}
		else
		{
			new->content = ft_substr(str, start, *i - start + 1);
			new->type = CHAR_WORD;
			*i = *i + 1;
		}
	}
	else
		return (-1);
	return (0);
}

int	tokenize_special_char(char *str, t_token *new, int *i)
{
	// how to move within string so that in the lexer func it moves to the next char?
	// and how to make the function go: this token is done go to the next token?
	//is checking for a space after special char necessary?
	if (str[*i] == '|') // ?
	{
		new->type = CHAR_PIPE;
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		new->type = CHAR_DLESS;
		(*i) = (*i) + 2;
	}
	else if (str[*i] == '<')
	{
		new->type = CHAR_LESS;
		(*i)++;
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		new->type = CHAR_DGREAT;
		(*i) = (*i) + 2;
	}
	else if (str[*i] == '>')
	{
		new->type = CHAR_GREAT;
		(*i)++;
	}
	else
	{
		//problem: always goes into this condition when end of the line
		printf("error in check_special\n");
		return (-1);
	}
	// printf("new added is %s and type is %d\n", new->content, new->type);
	return (0);
}

void	lexer(char *str, t_token **token)
{
	t_token		**head;
	t_token		*new;
	int			i;
	t_tree_node	*root;

	*head = NULL;
	i = 0;
	while (str[i] != '\0')//would it be possible to not have it end with \n
	{
		new = initialize();
		while (ft_iswhitespace(str[i]))
			i++;
		if (ft_strchr("|><", str[i]))
		{
			if (tokenize_special_char(str, new, &i) == -1)
				return ;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if (tokenize_quote_word(str, new, &i) == -1)
				return ;
		}
		else
			tokenize_word(str, new, &i);
		ft_listadd_back(head, new);
	}
	token = head;
	lst_print(*token);
	root = parser(*token);
	// print_tree(root);
}
