#include "minishell.h"

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

void	execute_pipe(t_pipe_node pipe, char **envp)
{
	execute_tree(pipe.left, envp);
	execute_tree(pipe.right, envp);
}

void	execute_cmd(t_cmd_node cmd, char **envp)
{
	int	nb;

	nb = count_node(cmd.tokens);
	execution(cmd.tokens, nb, envp);
}

void	execute_tree(t_tree_node *tree, char **envp)
{
	if (tree->type == PIPE_NODE)
		execute_pipe(tree->data.pipe, envp);
	else
		execute_cmd(tree->data.cmd, envp);
}

int	execution(t_token *token, int nb, char **envp)
{
	char	**argument;

	argument = malloc((nb + 1) * sizeof(char *));
	if (!argument)
		return(-1);//error
	argument[nb] = NULL;
	nb = 0;
	while (token)
	{
		argument[nb] = ft_strdup(token->content);
		nb++;
		token = token->next;
	}
	//put built-in logic here.
	if(is_built_in(argument[0]))
	{
		printf("BUILT_IN\n");
		return(exec_built_in(argument, nb));
	}
	if (fork() == 0)
	{
		if (execute_program(argument, envp) == -1)
			return (-1); // error
		return (0);
	}
	else
	{
		wait(NULL);
		free_array(argument);
		return (0);
	}
}
