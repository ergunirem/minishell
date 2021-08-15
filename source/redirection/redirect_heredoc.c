/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:06:54 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:09:41 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	str_cmp(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 != len2)
		return (-1);
	else
		return (ft_memcmp(str1, str2, len1));
}

static void	with_expansion(char *delimiter, char *newline, int *fd)
{
	int	len_nl;

	if (!newline)
		exit(0);
	while (str_cmp(delimiter, newline) != 0)
	{
		if (ft_strrchr(newline, '$'))
			newline = just_expand(newline);
		len_nl = ft_strlen(newline);
		write(fd[1], newline, len_nl);
		write(fd[1], "\n", 1);
		free(newline);
		newline = readline(">");
		if (!newline)
			exit(0);
	}
	free(newline);
}

static void	without_expansion(char *delimiter, char *newline, int *fd)
{
	int	len_nl;

	while (str_cmp(delimiter, newline) != 0)
	{
		len_nl = ft_strlen(newline);
		write(fd[1], newline, len_nl);
		write(fd[1], "\n", 1);
		free(newline);
		newline = readline(">");
		if (!newline)
			break ;
	}
	free(newline);
}

static void	free_two(char *a, char *b)
{
	if (a)
		free(a);
	else if (b)
		free(b);
	else
		return ;
}

int	exec_heredoc(t_token *token, t_context *ctx, int count)
{
	char	*delimiter;
	char	*new_delimiter;
	char	*newline;
	int		len;
	int		fd[2];

	delimiter = ft_strdup(token->next->content);
	if (!delimiter)
		return (-1);
	new_delimiter = NULL;
	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len - 1] == '\"'))
		new_delimiter = ft_substr(delimiter, 1, len - 2);
	if (pipe(fd) == -1)
		return (-1);
	newline = readline(">");
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		|| (delimiter[0] == '\"' && delimiter[len - 1] == '\"'))
		without_expansion(new_delimiter, newline, fd);
	else
		with_expansion(delimiter, newline, fd);
	free_two(new_delimiter, delimiter);
	close(fd[1]);
	return (fd[0]);
}
