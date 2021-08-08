#include "../../include/minishell.h"
#include "../../include/built_in.h"

static int	pipe_left(t_pipe_node *pipe, char **envp, int *p, t_context *ctx)
{
	int			count;
	t_context	branch;

	branch = *ctx;
	branch.fd[1] = p[1];
	branch.fd_close = p[0];
	count = exec_node(pipe->left, &branch, envp);
	return (count);
}

static int	pipe_right(t_pipe_node *pipe, char **envp, int *p, t_context *ctx)
{
	int			count;
	t_context	branch;

	branch = *ctx;
	branch.fd[0] = p[0];
	branch.fd_close = p[1];
	count = exec_node(pipe->right, &branch, envp);
	return (count);
}

int	exec_pipe(t_tree_node *node, t_context *ctx, char **envp)
{
	int			p[2];
	int			children;
	int			count;

	if (pipe(p) == -1)
	{
		error_msg(strerror(errno), "1");
		return (-1);
	}
	children = 0;
	count = pipe_left(&(node->data.pipe), envp, p, ctx);
	if (count < 0)
		return (-1);
	else
		children = children + count;
	close(p[1]);
	count = pipe_right(&(node->data.pipe), envp, p, ctx);
	if (count < 0)
		return (-1);
	else
		children = children + count;
	close(p[0]);
	return (children);
}
