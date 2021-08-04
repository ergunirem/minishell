#include "../include/minishell.h"

static volatile sig_atomic_t	keep_running = 1; //2 global vars?
t_env	g_env;

void	inthandler(int _)
{
	(void)_;
	keep_running = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_tree_node	*root;

	init_variables(envp);
	while (keep_running)
	{
		line = readline("Minishell$ ");
		printf("Check\n");
		if (line && *line)
    		add_history (line);
		// add_history(line);
		tokens = NULL;
		if (!lexer(line, &tokens))
			continue ;
		// print_tokens(tokens);
		if (check_list(tokens))
		{
			root = parser(&tokens);
			exec(root, envp);
			// print_tree(root);
			free_tree(root);
		}
		free_tokens(&tokens);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	//do I need to free dynamically allocated list on global g_env? 	// free_env();
	return (0);
}
