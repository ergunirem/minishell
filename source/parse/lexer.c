#include "../../include/minishell.h"

static t_token	*initialize_token(void)
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

static void	tokenize_word(char *str, t_token *new, int *i)
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

static bool	tokenize_quote_word(char *str, t_token *new, int *i)
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
		return (false); //ask why this error? can we print smth? connect this to lexer-main error chain?
	return (true);
}

static void	tokenize_special_char(char *str, t_token *new, int *i)
{
	if (str[*i] == '|')
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
}

bool	lexer(char *str, t_token **tokens)
{
	t_token		*new;
	int			i;

	i = 0;
	if (!str)
		return (true);
	while (str[i] != '\0')
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i] == '\0')
			return (true);
		new = initialize_token();
		if (!new)
			return (lexer_error(tokens, MALLOC_ERROR));
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			tokenize_special_char(str, new, &i);
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if (!tokenize_quote_word(str, new, &i))
				return (lexer_error(tokens, QUOTE_ERROR));
		}
		else
			tokenize_word(str, new, &i);
		ft_listadd_back(tokens, new);
	}
	return (true);
}
