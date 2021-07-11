#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include "token.h"
# include "parser.h"
# include "error.h"

typedef enum { FALSE, TRUE } bool;

void	lst_print(t_token *list);
bool	check_list(t_token *tokens);
bool	error_msg(char *msg);
void	free_tokens(t_token **tokens);
void	free_tree(t_tree_node *tree);
void	free_array(char **array);
int		execution(t_token *token, int nb, char **envp);
void	execute_tree(t_tree_node *tree, char **envp);
int	execute_program(char **argument, char **envp);
// void	print_tree(t_ASTtree *tree);

#endif
