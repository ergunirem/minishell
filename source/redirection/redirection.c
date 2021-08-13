#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/minishell.h"

static int	redirect_output(t_token **token, t_context *ctx, int count)
{
	int		fd;
	char	*file;

	file = ft_strdup((*token)->next->content);
	if (!file)
		return (error_msg(strerror(errno), "1"));
	file = remove_quotes_and_expand(file);
	if (!file)
		return (error_msg(strerror(errno), "1"));
	if ((*token)->type == CHAR_GREAT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if ((*token)->type == CHAR_DGREAT)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	ctx->redir[count] = fd;
	if (fd < 0)
		return (error_new_bool(NULL,
				(*token)->next->content, strerror(errno), 1));
	else
	{
		ctx->fd[1] = fd;
		(*token) = (*token)->next->next;
	}
	free(file);
	return (1);
}

static int	redirect_input(t_token **token, t_context *ctx, int count)
{
	int		fd;
	char	*file;

	file = ft_strdup((*token)->next->content);
	if (!file)
		return (error_msg(strerror(errno), "1"));
	file = remove_quotes_and_expand(file);
	if (!file)
		return (error_msg(strerror(errno), "1"));
	fd = open(file, O_RDONLY);
	ctx->redir[count] = fd;
	if (fd < 0)
		return (error_new_bool(NULL,
				(*token)->next->content, strerror(errno), 1));
	else
	{
		ctx->fd[0] = fd;
		(*token) = (*token)->next->next;
	}
	return (1);
}

static int	redirect_heredoc(t_token **token, t_context *ctx, int count)
{
	ctx->fd[0] = exec_heredoc(*token, ctx, count);
	if (ctx->fd[0] < 0)
		return (error_msg(strerror(errno), "1"));
	ctx->redir[count] = ctx->fd[0];
	(*token) = (*token)->next->next;
	return (1);
}

int	redirection(t_token **token, t_context *ctx, int count)
{
	int		fd;
	char	*file;

	if ((*token)->type == CHAR_DLESS)
		return (redirect_heredoc(token, ctx, count));
	if ((*token)->type == CHAR_GREAT || (*token)->type == CHAR_DGREAT)
	{
		if (redirect_output(token, ctx, count) == 0)
			return (0);
	}
	else
	{
		if (redirect_input(token, ctx, count) == 0)
			return (0);
	}
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
