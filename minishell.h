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
}	t_token;

typedef struct s_ASTtree
{
	int					type;
	char				*content;
	struct s_ASTtree	*left;
	struct s_ASTtree	*right;
}	t_ASTtree;

// ENUM tree elements
enum e_TreeElement{
	CMD_LINE = 1,
	JOB = 2,
	WORD = 3,
	PIPE = 4,
};
// ENUM token type
enum e_TokenType{
	CHAR_PIPE = 'P',
	CHAR_LESS = 'L',
	CHAR_DLESS = 'D',
	CHAR_GREAT = 'G',
	CHAR_DGREAT = 'H',
	CHAR_WORD = 'W',
};

void	lexer(char *str, t_token **token);
void	lst_print(t_token *list);
void	parser(t_token *tokens, t_ASTtree **tree);
void	print_tree(t_ASTtree *tree);

#endif
