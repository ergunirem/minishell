/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:05:42 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:05:44 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
}	t_TokenType;

typedef struct s_token
{
	char			*content;
	t_TokenType		type;
	struct s_token	*next;
}	t_token;

bool	lexer(char *str, t_token **tokens);
void	print_tokens(t_token *list);
void	free_tokens(t_token **tokens);

#endif
