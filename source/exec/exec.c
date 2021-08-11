#include "../../include/minishell.h"
#include "../../include/built_in.h"

void	exec(t_tree_node *node, char **envp)
{
	int			children;
	t_context	ctx;
	int			stat;

	ctx = (t_context){{STDIN_FILENO, STDOUT_FILENO, 2}, -1, 0};
	children = exec_node(node, &ctx, envp);
	while (children > 0)
	{
		if (WIFSIGNALED(stat))
		{
			signal(SIGINT, handle_child_signal);
			signal(SIGQUIT, handle_child_signal);
		}
		wait(&stat);
		if (WIFEXITED(stat))
			set_var("PIPESTATUS", ft_itoa(WEXITSTATUS(stat)));
		signal(SIGINT, handle_parent_signal);
		signal(SIGQUIT, handle_parent_signal);
		children--;
	}
}

int	exec_node(t_tree_node *node, t_context *ctx, char **envp)
{
	if (node->type == CMD_NODE)
		return (exec_command(node, ctx, envp));
	if (node->type == PIPE_NODE)
		return (exec_pipe(node, ctx, envp));
	else
		return (0);
}

void	close_redirection(int *fd, int count)
{
	while (count > 0)
	{
		close(fd[count - 1]);
		count--;
	}
}

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
