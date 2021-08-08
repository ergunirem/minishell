#include "../../include/minishell.h"
#include "../../include/built_in.h"

#define FORK_CHILD 0

static int	initiate_redirection(t_token *token, t_context *ctx,
	int *argc, char ***argv)
{
	ctx->redir = malloc(argc[1] * sizeof(int));
	if (!ctx->redir && argc[1] > 0)
	{
		error_msg(strerror(errno), "1");
		return (-1);
	}
	argc[0] = argc[0] - argc[1] * 2;
	*argv = malloc((argc[0] + 1) * sizeof(char *));
	if (!argv)
	{
		error_msg(strerror(errno), "1");
		free(ctx->redir);
		return (-1);
	}
	return (argc[0]);
}

static int	parse_argument(char **argv, t_token *token, int *argc,
	t_context *ctx)
{
	argv[argc[0]] = NULL;
	argc[0] = 0;
	argc[1] = 0;
	while (token)
	{
		if (token->type != CHAR_WORD)
		{
			if (redirection(&token, ctx, argc[1]) == 0)
				return (1);
			argc[1]++;
		}
		else
		{
			argv[argc[0]] = ft_strdup(token->content);
			if (!(argv[argc[0]]))
			{
				free_array2(argv, argc[0]);
				return (1);
			}
			argv[argc[0]] = remove_quotes_and_expand(argv[argc[0]]);
			argc[0]++;
			token = token->next;
		}
	}
	return (0);
}

static int	check_buildin(char **argv, t_context *ctx, int *argc, char **envp)
{
	if (is_built_in(argv[0]))
	{
		exec_built_in(argv, argc[0], ctx, envp);
		close_redirection(ctx->redir, argc[1]);
		free_array(argv);
		free(ctx->redir);
		return (0);
	}
	else
		return (1);
}

static int	exec_existing_program(t_context *ctx, char **argv, char **envp)
{
	if (fork() == FORK_CHILD)
	{
		// signal(SIGINT, handle_child_signal);
		// signal(SIGQUIT, handle_child_signal);
		// g_env.is_forked = 1;
		// write(1, &g_env.is_forked, 1);
		// printf("%d\n", g_env.is_forked);
		dup2(ctx->fd[0], 0);
		dup2(ctx->fd[1], 1);
		dup2(ctx->fd[2], 2);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		if (execve(argv[0], argv, envp) == -1)
			return (error_new_bool(argv[0], NULL, strerror(errno), 1));
		else
			return (1);
	}
	return (1);
}

int	exec_command(t_tree_node *node, t_context *ctx, char **envp)
{
	int		argc[2];
	char	**argv;

	argv = NULL;
	argc[0] = count_node(node->data.cmd.tokens);
	argc[1] = count_redirection(node->data.cmd.tokens, ctx);
	argc[0] = initiate_redirection(node->data.cmd.tokens, ctx, argc, &argv);
	if (argc[0] == -1)
		return (-1);
	if (parse_argument(argv, node->data.cmd.tokens, argc, ctx))
		return (-1);
	if (check_buildin(argv, ctx, argc, envp) == 0)
		return (0);
	if (check_existing_program(&argv, envp) == 0)
		return (0);
	if (exec_existing_program(ctx, argv, envp) == 0)
		return (0);
	free_array(argv);
	close_redirection(ctx->redir, argc[1]);
	free(ctx->redir);
	return (1);
}
