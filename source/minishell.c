#include "../include/minishell.h"

// static volatile sig_atomic_t	keep_running = 1; //2 global vars?
t_env	g_env;

// void	inthandler(int _)
// {
// 	(void)_;
// 	keep_running = 0;
// }


int	lex_parse_execute(void)
{
	t_token *tokens;
	t_tree_node *root;

	signal(SIGINT, handle_parent_signal);
	printf(">%s\n", g_env.line);
	g_env.line = readline("Minishell$ ");
	// printf("Check\n");
	if (g_env.line)
		add_history(g_env.line);
	// add_history(line);
	tokens = NULL;
	lexer(g_env.line, &tokens);
	// print_tokens(tokens);ß
	if (check_list(tokens))
	{
		root = parser(&tokens);
		exec(root, g_env.envp);
		// print_tree(root);
		free_tree(root);
	}
	free_tokens(&tokens);
	if (g_env.line)
	{
		free(g_env.line);
		g_env.line = NULL;
	}
}

void	handle_parent_signal(int sig)
{
	ft_putstr_fd("\b\b  \b\b\b", 1);
	if (sig == SIGINT)
	{
		g_env.line = NULL;
		ft_putstr_fd("\n", 1);
		lex_parse_execute();

		// g_sh.last_status = 1;
	}
	// (void)sig;
	// if (write(1, "\n", 3) < 0)
	// 	return ;
	// return ;
}

int	main(int argc, char **argv, char **envp)
{
	// char		*line;


	if (init_env_variables(envp) == 1)
		return (1);
	signal(SIGINT, handle_parent_signal);
	// signal(SIGMINE, handle_parent_signal);
	// signal(SIGQUIT, handle_parent_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		lex_parse_execute();
	}
	//do I need to free dynamically allocated list on global g_env? 	// free_env();
	return (0);
}
