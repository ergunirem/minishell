#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
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
# include "built_in.h"
# include "environment.h"
# include <stdbool.h>
# include <string.h>
# include <errno.h>

// typedef enum { FALSE, TRUE } bool;

// typedef struct	s_context{
// 	int	fd[2];
// 	int fd_close;
// }	t_context;

void	lst_print(t_token *list);
bool	check_list(t_token *tokens);
bool	error_msg(char *msg);
void	free_tokens(t_token **tokens);
void	free_tree(t_tree_node *tree);
void	free_array(char **array);
int		execution(t_token *token, int nb, char **envp);
// void	execute_tree(t_tree_node *tree, char **envp);
// int		execute_program(char **argument, char **envp);
int	execute_existing_program(char **argument, char **envp);
void	ft_listadd_back(t_token **lst, t_token *new); //?move to libft
void	exec(t_tree_node *node, char **envp);

#endif
