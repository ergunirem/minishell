#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include "token.h"
# include "parser.h"
# include "error.h"
# include "built_in.h"
# include "environment.h"
# include "expansion.h"
# include "signal.h"
# include <stdbool.h>
# include <string.h>
# include <errno.h>

void	free_array(char **array);
void	free_array2(char **array, int n);
int		check_existing_program(char ***argument, char **envp);
void	ft_listadd_back(t_token **lst, t_token *new);
void	exec(t_tree_node *node, char **envp);

#endif
