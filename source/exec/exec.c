#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../include/minishell.h"
#include "../../include/built_in.h"

#define FORK_CHILD 0

static int	exec_node(t_tree_node *node, t_context *ctx, char **envp);
static int	exec_pipe(t_tree_node *node, t_context *ctx, char **envp);
static int	exec_command(t_tree_node *node, t_context *ctx, char **envp);
// static int	exec_command2(char **argv, int argc, int count, t_context *ctx, char **envp);
static int	exec_command2(t_token *token, int argc, t_context *ctx, char **envp);

static int	count_node(t_token *token)
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
	int			children;
	t_context	ctx;

	ctx = (t_context){{STDIN_FILENO, STDOUT_FILENO, 2}, -1, 0};
	children = exec_node(node, &ctx, envp);
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

static void	close_redirection(int *fd, int count)
{
	while (count > 0)
	{
		close(fd[count - 1]);
		count--;
	}
}

static int	exec_pipe(t_tree_node *node, t_context *ctx, char **envp)
{
	int			p[2];
	int			children;
	int			count;
	t_context	left_ctx;
	t_context	right_ctx;

	if (pipe(p) == -1)
	{
		error_msg(strerror(errno));
		return (-1);
	}
	children = 0;
	left_ctx = *ctx;
	left_ctx.fd[1] = p[1];
	left_ctx.fd_close = p[0];
	count = exec_node(node->data.pipe.left, &left_ctx, envp);
	if (count < 0)
		return (-1);
	else
		children = children + count;
	// children = children + exec_node(node->data.pipe.left, &left_ctx, envp);
	close(p[1]);
	right_ctx = *ctx;
	right_ctx.fd[0] = p[0];
	right_ctx.fd_close = p[1];
	// children = children + exec_node(node->data.pipe.right, &right_ctx, envp);
	count = exec_node(node->data.pipe.right, &right_ctx, envp);
	if (count < 0)
		return (-1);
	else
		children = children + count;
	close(p[0]);
	return (children);
}

static int	exec_command(t_tree_node *node, t_context *ctx, char **envp)
{
	int	argc;

	argc = count_node(node->data.cmd.tokens);
	return (exec_command2(node->data.cmd.tokens, argc, ctx, envp));
}

// static char	**parse_argv(t_token *token, t_context *ctx, char **argv)
// {
// 	int	count;
// 	int	argc;

// 	count = 0;
// 	argc = 0;
// 	while (token)
// 	{
// 		// if (token->type != CHAR_WORD && redirection(&token, ctx, count) == 0)
// 		// 	return (NULL);
// 		// else if (token->type != CHAR_WORD)
// 		// 	count++;
// 		if (token->type != CHAR_WORD)
// 		{
// 			if (redirection(&token, ctx, count) == 0)
// 				return (0);
// 			count++;
// 		}
// 		else
// 		{
// 			argv[argc] = ft_strdup(token->content);
// 			if (!argv[argc])
// 				return (error_msg_inclfree(strerror(errno), argv, argc + 1));
// 			argv[argc] = remove_quotes_and_expand(argv[argc]);
// 			if (!argv[argc])
// 				return (error_msg_inclfree(strerror(errno), argv, argc + 1));
// 			argc++;
// 			token = token->next;
// 		}
// 	}
// 	return (argv);
// }

// static int	exec_command(t_tree_node *node, t_context *ctx, char **envp)
// {
// 	int		argc;
// 	int		count;
// 	char	**argv;

// 	argc = count_node(node->data.cmd.tokens);
// 	count = count_redirection(node->data.cmd.tokens, ctx);
// 	ctx->redir = malloc(count * sizeof(int));
// 	if (!ctx->redir && count > 0)
// 	{
// 		error_msg(strerror(errno));
// 		return (-1);
// 	}
// 	argc = argc - count * 2;
// 	argv = malloc((argc + 1) * sizeof(char *));
// 	if (!argv)
// 	{
// 		error_msg(strerror(errno));
// 		return (-1);
// 	}
// 	argv = parse_argv(node->data.cmd.tokens, ctx, argv);
// 	if (!argv)
// 		return (0);
// 	return (exec_command2(argv, argc, count, ctx, envp));
// }

// static int	exec_command2(char **argv, int argc, int count, t_context *ctx, char **envp)
// {
// 	if (is_built_in(argv[0]))
// 	{
// 		exec_built_in(argv, argc, ctx, envp);
// 		close_redirection(ctx->redir, count);
// 		return (0);
// 	}
// 	if (check_existing_program(&argv, envp) == 0)
// 		return (0);
// 	if (fork() == FORK_CHILD)
// 	{
// 		dup2(ctx->fd[0], 0);
// 		dup2(ctx->fd[1], 1);
// 		dup2(ctx->fd[2], 2);
// 		if (ctx->fd_close >= 0)
// 			close(ctx->fd_close);
// 		if (execve(argv[0], argv, envp) == -1)
// 			return (error_new_bool(argv[0], NULL, strerror(errno), 1));
// 	}
// 	free_array(argv);
// 	close_redirection(ctx->redir, count);
// 	free(ctx->redir);
// 	return (1);
// }

static int	exec_command2(t_token *token, int argc, t_context *ctx, char **envp)
{
	char	**argv;
	int		count;

	count = count_redirection(token, ctx);
	ctx->redir = malloc(count * sizeof(int));
	if (!ctx->redir && count > 0)
	{
		error_msg(strerror(errno));
		return (-1);
	}
	argc = argc - count * 2;
	argv = malloc((argc + 1) * sizeof(char *));
	if (!argv)
	{
		error_msg(strerror(errno));
		return (-1);
	}
	argv[argc] = NULL;
	argc = 0;
	count = 0;
	while (token)
	{
		if (token->type != CHAR_WORD)
		{
			if (redirection(&token, ctx, count) == 0)
				return (0);
			count++;
		}
		else
		{
			argv[argc] = ft_strdup(token->content);
			argv[argc] = remove_quotes_and_expand(argv[argc]);
			argc++;
			token = token->next;
		}
	}
	if (is_built_in(argv[0]))
	{
		exec_built_in(argv, argc, ctx, envp);
		close_redirection(ctx->redir, count);
		return (0);
	}
	if (check_existing_program(&argv, envp) == 0)
		return (0);
	if (fork() == FORK_CHILD)
	{
		dup2(ctx->fd[0], 0);
		dup2(ctx->fd[1], 1);
		dup2(ctx->fd[2], 2);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		if (execve(argv[0], argv, envp) == -1)
			return (error_new_bool(argv[0], NULL, strerror(errno), 1));
	}
	free_array(argv);
	close_redirection(ctx->redir, count);
	free(ctx->redir);
	// return (1);
}
