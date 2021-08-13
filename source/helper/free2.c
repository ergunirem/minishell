#include "../../include/minishell.h"

int	free_set(char **argv, t_context *ctx, int count, int n)
{
	if (!argv)
		free_array(argv);
	close_redirection(ctx->redir, count);
	if (!ctx->redir)
		free(ctx->redir);
	return (n);
}
