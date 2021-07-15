#include "../include/minishell.h"

static volatile sig_atomic_t	keep_running = 1;

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

	while (keep_running)
	{
		line = readline("Minishell$ ");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (!ft_strncmp(line, "exit", 5))
			break;
		lexer(line, &tokens);
		lst_print(tokens);
		if(check_list(tokens))
		{
			root = parser(&tokens);
			init_variables(envp);
			// execution(root->data.cmd.tokens, envp);
			execute_tree(root, envp);
			print_tree(root);
			free_tree(root);
		}
		free_tokens(&tokens);
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int			pid;
// 	int			s_wait;
// 	char		*line;
// 	t_token		*tokens;
// 	t_tree_node	*root;

// 	pid = fork();
// 	// if (pid < 0)
// 	// 	ft_error();//to add the error handling function
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, inthandler);
// 		while (keep_running)
// 		{
// 			line = readline("Minishell$ ");
// 			if (ft_strlen(line) > 0)
// 				add_history(line);
// 			if (!ft_strncmp(line, "exit", 5))
// 				break;
// 			lexer(line, &tokens);
// 			lst_print(tokens);
// 			if(check_list(tokens))
// 			{
// 				root = parser(&tokens);
// 				execution(root->data.cmd.tokens, envp);
// 				print_tree(root);
// 				free_tree(root);
// 			}
// 			free_tokens(&tokens);
// 		}
// 	}
// 	else
// 	{
// 		wait(&s_wait);
// 		// system("leaks minishell");
// 		return (0);
// 	}
// }
