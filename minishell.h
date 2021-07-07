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


void	lst_print(t_token *list);
// void	print_tree(t_ASTtree *tree);

#endif
