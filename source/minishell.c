#include "../include/minishell.h"

t_env	g_env;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token *tokens;
	t_tree_node *root;

	if (init_env_variables(envp) == 1)
		return (1);
	signal(SIGINT, handle_parent_signal);
	signal(SIGQUIT, handle_parent_signal);
	while (1)
	{
		line = readline("Minishell$ ");
		// printf("Check\n");
		if(!line)
			return (handle_ctrl_d());
		printf("%d\n", g_env.is_forked);
		write(1,"IN\n", 3);
		add_history(line);
		tokens = NULL;
		lexer(line, &tokens);
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
