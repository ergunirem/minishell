/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 11:59:21 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/10 13:59:13 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

static bool	check_quote(char *str, int *i)
{
	char	quote;

	while (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[*i];
		*i = *i + 1;
		if (!ft_strchr(str + *i, quote))
			return (false);
		while (str[*i] != quote)
			(*i)++;
		(*i)++;
	}
	return (true);
}

static bool	tokenize_word(char *str, t_token *new, int *i)
{
	int	start;
	int	n;

	start = *i;
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (ft_strchr("|<>", str[*i]))
			break ;
		if (ft_strchr("\'\"", str[*i]))
		{
			if (!check_quote(str, i))
				return (false);
		}
		else
			(*i)++;
	}
	new->content = ft_substr(str, start, *i - start);
	if (!new->content)
		return (false);
	new->type = CHAR_WORD;
	if (str[*i] != '\0' && !ft_strchr("|<>", str[*i]))
		*i = *i + 1;
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

	if (!str)
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i] == '\0')
			return (true);
		new = initialize_token();
		if (!new)
			return (lexer_error(NULL, MALLOC_ERROR, "1"));
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			tokenize_special_char(str, new, &i);
		else
		{
			if (!tokenize_word(str, new, &i))
				return (lexer_error(new, QUOTE_ERROR, "2"));
		}
		ft_listadd_back(tokens, new);
	}
	return (true);
}
