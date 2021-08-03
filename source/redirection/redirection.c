#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/minishell.h"

static int redirect_output(char c, char *file)
{
	int	fd;

	if (c == CHAR_GREAT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT);
	else if (c == CHAR_DGREAT)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND);
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

	if (!token->next || !token->next->content)
		return (NULL);//error as nothing follow the redirection operator
	if (token->type == CHAR_GREAT || token->type == CHAR_DGREAT)
	{
		fd = redirect_output(token->type, token->next->content);
		printf("open fd is %d\n", fd);
		if (fd < 0)
			return (NULL); //error when try to open file
		else
		{
			ctx->fd[1] = fd;
			// ctx->fd_close = fd;
			return (token->next->next);
		}
	}
	// if (token->type == CHAR_DGREAT)
	// {

	// }
	// if (token->type == CHAR_LESS)
	// {

	// }
	// if (token->type == CHAR_DLESS)
	// {
		
	// }
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
