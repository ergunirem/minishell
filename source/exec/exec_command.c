#include "../../include/minishell.h"
#include "../../include/built_in.h"

#define FORK_CHILD 0

static int	initiate_redirection(t_token *token, t_context *ctx,
								int *argc, char ***argv)
{
	int	i;

	i = 0;
	ctx->redir = malloc(argc[1] * sizeof(int));
	if (!ctx->redir && argc[1] > 0)
	{
		error_msg(strerror(errno), "1");
		return (-1);
	}
	while (i < argc[1])
	{
		ctx->redir[i] = -1;
		i++;
	}
	argc[0] = argc[0] - argc[1] * 2;
	*argv = malloc((argc[0] + 1) * sizeof(char *));
	(*argv)[argc[0]] = NULL;
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
			// printf("arg0 is %s\n", argv[0]);
			argv[argc[0]] = remove_quotes_and_expand(argv[argc[0]]);
			// printf("arg0 after adjustment is %s\n", argv[0]);
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
		if (exec_built_in(argv, argc[0], ctx, envp) == 0)
			return (0);
	}
	return (-1);
}

static int	exec_existing_program(t_context *ctx, char **argv, char **envp)
{
	int	result;

	result = fork();
	if (result == FORK_CHILD)
	{
		g_env.is_forked = 1;
		dup2(ctx->fd[0], 0);
		dup2(ctx->fd[1], 1);
		dup2(ctx->fd[2], 2);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		if (execve(argv[0], argv, envp) == -1)
		{
			set_var("PIPESTATUS", "1");
			return (error_new_bool(argv[0], NULL, strerror(errno), 1));
		}
	}
	return (1);
}

int	count_whitespace(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i + 1])
	{
		if (ft_iswhitespace(str[i]) && !ft_iswhitespace(str[i + 1]))
			count++;
		i++;
	}
	// printf("count is %d\n", count);
	if (ft_iswhitespace(str[0]) && i == 0)
		return (-1);//env is only white space =>should only pomp a new line
	else if (ft_iswhitespace(str[0]))
		return (count - 1);
	else
		return (count);
}

void	parse_nonwhitesp(char *str, char **argv, int *k)
{
	int	i;
	int	len;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && (!ft_iswhitespace(str[i]))) || (!ft_iswhitespace(str[i]) && i > 0 && ft_iswhitespace(str[i - 1])))
		{
			len = 0;
			while (str[i + len])
			{
				if (!ft_iswhitespace(str[i + len]) && (!str[i + len + 1] || ft_iswhitespace(str[i + len + 1])))
				{
					argv[*k] = ft_substr(str, i, len + 1);
					// printf("argv %d is %s i is %d len is %d\n", *k, argv[*k], i, len);
					(*k)++;
					break;
				}
				len++;
			}
			i = i + len;
		}
		i++;
	}
}

int	check_complexcmd (char ***argv, int *argc)
{
	int	i;
	int	j;
	int	k;
	char **argv2;

	i = count_whitespace((*argv)[0]);
	if (i == -1)
		return (0);
	if (i == 0)
		return (1);
	j = 0;
	argv2 = malloc((argc[0] + 1 + i) * sizeof(char *));
	argv2[argc[0] + i] = NULL;
	if (!argv2)
		return (error_new_bool(NULL, NULL, strerror(errno), 2));
	parse_nonwhitesp((*argv)[0], argv2, &j);
	// printf("j is %d and i is %d\n", j, i);
	while (j < argc[0] + 1 + i)
	{
		argv2[j] = ft_strdup((*argv)[j - i]);
		// printf("argv2 %d is %s\n", j, argv2[j]);
		j++;
	}
	free_array(*argv);
	*argv = argv2;
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
		return (free_set(argv, ctx, argc[1], -1));
	if (check_complexcmd(&argv, argc) == 0)
		return (-1);
	if (check_buildin(argv, ctx, argc, envp) == 0)
		return (free_set(argv, ctx, argc[1], 0));
	if (check_existing_program(&argv, envp) == 0)
		return (free_set(argv, ctx, argc[1], 0));
	if (exec_existing_program(ctx, argv, envp) == 0)
		return (free_set(argv, ctx, argc[1], 0));
	return (free_set(argv, ctx, argc[1], 1));
}
