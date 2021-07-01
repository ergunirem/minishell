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
	char			*content;
	char			type;
	struct s_token	*next;
} t_token;

// ENUM TOKEN TYPES
enum TokenType{
	CHAR_PIPE = 'P',
	CHAR_LESS = 'L',
	CHAR_DLESS = 'D',
	CHAR_GREAT = 'G',
	CHAR_DGREAT = 'H',
	CHAR_WORD = 'W',
};

void	lexer(char *str, t_token **token);
void	lst_print(t_token *list);

#endif
