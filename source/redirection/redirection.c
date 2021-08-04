#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/minishell.h"

static int	redirect_output(char c, char *file)
{
	int	fd;

	if (c == CHAR_GREAT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (c == CHAR_DGREAT)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static int	redirect_input(char c, char *file)
{
	int	fd;

	if (c == CHAR_LESS)
		fd = open(file, O_RDONLY);
	return (fd);
}

int	redirection(t_token **token, t_context *ctx, int count)
{
	int	fd;
	char	*file;

	file = ft_strdup((*token)->next->content);
	if ((*token)->type == CHAR_DLESS)//move the heredoc at the first place, as if EOF with quote, do not expand
	{
		ctx->fd[0] = exec_heredoc(*token, file, ctx, count);//check input if it is -1
		ctx->redir[count] = ctx->fd[0];
		(*token) = (*token)->next->next;
	}
	file = remove_quotes_and_expand(file);
	if ((*token)->type == CHAR_GREAT || (*token)->type == CHAR_DGREAT)
	{
		fd = redirect_output((*token)->type, file);
		ctx->redir[count] = fd;
		if (fd < 0)
			return (error_new_bool(NULL, (*token)->next->content, strerror(errno), 1));
		else
		{
			ctx->fd[1] = fd;
			(*token) = (*token)->next->next;
		}
	}
	else
	{
		fd = redirect_input((*token)->type, file);
		ctx->redir[count] = fd;
		if (fd < 0)
			return (error_new_bool(NULL, (*token)->next->content, strerror(errno), 1));
		else
		{
			ctx->fd[0] = fd;
			(*token) = (*token)->next->next;
		}
	}
	free(file);
	return (1);
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
