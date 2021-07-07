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
# include "parser.h"

// ENUM token type
typedef enum e_TokenType{
	CHAR_PIPE = 'P',
	CHAR_LESS = 'L',
	CHAR_DLESS = 'D',
	CHAR_GREAT = 'G',
	CHAR_DGREAT = 'H',
	CHAR_WORD = 'W',
} t_TokenType;

typedef struct s_token
{
	char			*content;
	t_TokenType		type;
	struct s_token	*next;
}	t_token;

void	lexer(char *str, t_token **token);
void	lst_print(t_token *list);
// void	print_tree(t_ASTtree *tree);

#endif
