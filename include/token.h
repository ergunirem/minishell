#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>

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

bool	lexer(char *str, t_token **tokens);

#endif
