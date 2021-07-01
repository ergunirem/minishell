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
	int		type;
	struct s_token *next;
} t_token;

// ENUM TOKEN TYPES
enum TokenType{
	CHAR_PIPE = '|',
	CHAR_LESS = '<',
	CHAR_DLESS = '<<',
	CHAR_GREAT = '>',
	CHAR_DGREAT = '>>',
	CHAR_WORD = 'W',
};

void	lexer(char *str, t_token **token);
void	lst_print(t_token *list);

#endif
