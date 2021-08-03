#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/minishell.h"

static int redirect_output(char c, char *file)
{
	int	fd;

	if (c == CHAR_GREAT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (c == CHAR_DGREAT)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static int redirect_input(char c, char *file)
{
	int	fd;

	if (c == CHAR_LESS)
		fd = open(file, O_RDONLY);
	// else if (c == CHAR_DGREAT)
	// 	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

// static int redirect_input(char c, char *file)
// {
// 	int	fd;

// 	if (c == CHAR_LESS)
// 		fd = open(file, O_RDONLY);
// 	else if (c == CHAR_DGREAT)
// 		fd = open(file, O_CREAT | O_WRONLY);
// 	return (fd);
// }

t_token	*redirection(t_token *token, t_context *ctx)
{
	int	fd;
	char	*file;

	if (!token->next || !token->next->content)
		return (NULL);//error as nothing follow the redirection operator
	file = ft_strdup(token->next->content);
	if (token->type == CHAR_DLESS)//move the heredoc at the first place, as if EOF with quote, do not expand
	{
		ctx->fd[0] = exec_heredoc(token, file, ctx, count);//check input if it is -1
		ctx->redir[count] = ctx->fd[0];
		if (token->next->next)
			return (token->next->next);
		else
			return (NULL);
	}
	file = remove_and_expand(file);
	if (token->type == CHAR_GREAT || token->type == CHAR_DGREAT)
	{
		fd = redirect_output(token->type, file);
		// printf("open fd is %d\n", fd);
		ctx->redir[1] = fd;
		// printf("redir[0] and redir[1] is %d %d\n", ctx->redir[0], ctx->redir[1]);
		if (fd < 0)
			return (NULL); //error when try to open file
		else
		{
			ctx->fd[1] = fd;
			return (token->next->next);
		}
	}
	if (token->type == CHAR_LESS)
	{
		fd = redirect_input(token->type, file);
		ctx->redir[0] = fd;
		if (fd < 0)
			return (NULL); //error when try to open file
		else
		{
			ctx->fd[0] = fd;
			return (token->next->next);
		}
	}
	free(file);
}

int	count_redirection(t_token *token, t_context *ctx)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type != CHAR_WORD)
		{
			if (!token->next || !token->next->content)
				return (-1);
			else
			{
				count++;
				token = token->next->next;
			}
		}
		else
			token = token->next;
	}
	return (count);
}
