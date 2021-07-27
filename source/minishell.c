#include "../include/minishell.h"

static volatile sig_atomic_t	keep_running = 1;
t_env	g_env;

void	inthandler(int _)
{
	(void)_;
	keep_running = 0;
}

int	main(int argc, char **argv, char **envp)
{
	int			pid;
	int			s_wait;
	char		*line;
	t_token		*tokens;
	t_tree_node	*root;

	init_variables(envp);
	while (keep_running)
	{
		line = readline("Minishell$ ");
		add_history(line);
		tokens = NULL;
		if(!lexer(line, &tokens))
			continue ;
		lst_print(tokens);
		if(check_list(tokens))
		{
			root = parser(&tokens);
			// execution(root->data.cmd.tokens, envp);
			// execute_tree(root, envp);
			exec(root, envp);
			// print_tree(root);
			free_tree(root);
		}
		free_tokens(&tokens);
	}
	//do I need to free dynamically allocated list on global g_env?
	// free_env();
	return (0);
}
