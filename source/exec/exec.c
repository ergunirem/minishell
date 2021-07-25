#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../include/minishell.h"
#include "../../include/built_in.h"

#define FORK_CHILD 0

static int	exec_node(t_tree_node *node, t_context *ctx, char **envp);
static int	exec_pipe(t_tree_node *node, t_context *ctx, char **envp);
static int	exec_command(t_tree_node *node, t_context *ctx, char **envp);
static int	exec_command2(t_token *token, int argc, t_context *ctx, char **envp);

int	count_node(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	exec(t_tree_node *node, char **envp)
{
	int	children;

	t_context ctx = {{STDIN_FILENO, STDOUT_FILENO}, -1}; //initialize the context struct with stdin, stdout
	children = exec_node(node, &ctx, envp);//calculate how many waits from the children processes
	while (children > 0)
	{
		wait(NULL);
		children--;
	}
}

static int	exec_node(t_tree_node *node, t_context *ctx, char **envp)
{
	if (node->type == CMD_NODE)
		return (exec_command(node, ctx, envp));
	if (node->type == PIPE_NODE)
		return (exec_pipe(node, ctx, envp));
	else
		return (0);
}

static int	exec_pipe(t_tree_node *node, t_context *ctx, char **envp)
{
	int			p[2];
	int			children;
	t_context	left_ctx;
	t_context	right_ctx;

	pipe(p);// add error check for pipe (if pipe(p) == -1)
	children = 0;
	left_ctx = *ctx;
	left_ctx.fd[1] = p[1];
	left_ctx.fd_close = p[0];
	children = children + exec_node(node->data.pipe.left, &left_ctx, envp);
	close(p[1]);
	right_ctx = *ctx;
	right_ctx.fd[0] = p[0];
	right_ctx.fd_close = p[1];
	children = children + exec_node(node->data.pipe.right, &right_ctx, envp);
	close(p[0]);
	return (children);
}

static int	exec_command(t_tree_node *node, t_context *ctx, char **envp)
{
	int	argc;

	argc = count_node(node->data.cmd.tokens);
	return (exec_command2(node->data.cmd.tokens, argc, ctx, envp));
}

static int	exec_command2(t_token *token, int argc, t_context *ctx, char **envp)
{
	char	**argv;

	argv = malloc((argc + 1) * sizeof(char *));
	if (!argv)
		return (-1);
	argv[argc] = NULL;
	argc = 0;
	while (token)
	{
		argv[argc] = ft_strdup(token->content);
		argc++;
		token = token->next;
	}
	if (is_built_in(argv[0]))
	{
		exec_built_in(argv, argc, ctx, envp);
		return (0);
	}
	if (fork() == FORK_CHILD)
	{
		dup2(ctx->fd[0], 0);
		dup2(ctx->fd[1], 1);
		dup2(ctx->fd[2], 2); //stderr ?not sure?
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		if (execute_existing_program(argv, envp) == -1)
			return (-1);
	}
	free_array(argv);
	return (1);
}
