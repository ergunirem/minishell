/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:08:29 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:18:32 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	g_env;

void	read_and_add_to_history(char **line)
{
	*line = readline("Minishell$ ");
	if (!*line)
		handle_ctrl_d();
	add_history(*line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_tree_node	*root;

	if (init_env_variables(envp) == 1)
		return (1);
	signal(SIGINT, handle_parent_signal);
	signal(SIGQUIT, handle_parent_signal);
	while (1)
	{
		read_and_add_to_history(&line);
		tokens = NULL;
		if (!lexer(line, &tokens))
			free_tokens(&tokens);
		if (check_list(tokens))
		{
			root = parser(&tokens);
			exec(root, envp);
			free_tree(root);
		}
		free_tokens(&tokens);
		free(line);
		line = NULL;
		g_env.pipe_exit = 0;
	}
}
