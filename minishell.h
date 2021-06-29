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

typedef struct s_token
{
	char	*content;
	char	*type;
	struct s_token *next;
} t_token;

void	lexer(char *str, t_token **token);

#endif
